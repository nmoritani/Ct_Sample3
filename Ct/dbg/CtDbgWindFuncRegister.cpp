#include "CtDbgWindFuncRegister.h"
#include "CtWindowController.h"
#include "CtFuncIDString.h"
#include "CtWindowIDString.h"

#include <CtPlatforms.h>

CtDbgWindFuncRegister::CtDbgWindFuncRegister()
{
	syswrap_delay_thread(200);
	CtWindowController::getInstance()->registerWindowFunc(Window_005, FuncID_001, (CtWindowFunc)windFunc1);
	CtWindowController::getInstance()->registerWindowFunc(Window_005, FuncID_002, (CtWindowFunc)windFunc2);
	CtWindowController::getInstance()->registerWindowFunc(Window_005, FuncID_003, (CtWindowFunc)windFunc3);
	CtWindowController::getInstance()->registerWindowFunc(Window_005, FuncID_004, (CtWindowFunc)windFunc4);
#ifdef WIN32_GUI_SIM
	// APL‚ªŽg‚¤‚½‚ßSim§ŒÀ‚ ‚è
	CtWindowController::getInstance()->registerWindowFunc((CtWindowID)0xFFFFFFFF, FuncID_ALL, (CtWindowFunc)windFuncAll);
#endif
}
CtDbgWindFuncRegister::~CtDbgWindFuncRegister()
{
	CtWindowController::getInstance()->unregisterWindowFunc(FuncID_001);
	CtWindowController::getInstance()->unregisterWindowFunc(FuncID_002);
	CtWindowController::getInstance()->unregisterWindowFunc(FuncID_003);
	CtWindowController::getInstance()->unregisterWindowFunc(FuncID_004);
	CtWindowController::getInstance()->unregisterWindowFunc(FuncID_ALL);
}

void CtDbgWindFuncRegister::windFunc1(CtScreenSel screen, CtWindowID id, CtFuncID funcId, CtWindowContents* contents) {
	CtDebugPrint(CtDbg, "WindFunc1 : FuncID[ %d ]\n", funcId);
}
void CtDbgWindFuncRegister::windFunc2(CtScreenSel screen, CtWindowID id, CtFuncID funcId, CtWindowContents* contents) {
	CtDebugPrint(CtDbg, "WindFunc2 : FuncID[ %d ]\n", funcId);
}
void CtDbgWindFuncRegister::windFunc3(CtScreenSel screen, CtWindowID id, CtFuncID funcId, CtWindowContents* contents) {
	CtDebugPrint(CtDbg, "WindFunc3 : FuncID[ %d ]\n", funcId);
}
void CtDbgWindFuncRegister::windFunc4(CtScreenSel screen, CtWindowID id, CtFuncID funcId, CtWindowContents* contents) {
	CtDebugPrint(CtDbg, "WindFunc4 : FuncID[ %d ]\n", funcId);
}
void CtDbgWindFuncRegister::windFuncAll(CtScreenSel screen, CtWindowID id, CtFuncID funcId, CtWindowContents* contents) {
	CtDebugPrint(CtDbg, "Call WindowID [ %s ] FuncID[ %3d ][ %s ]\n", CtWindowIDString::getString(id), funcId, CtFuncIDString::getString(funcId));
}
