/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtEventInterface
 */
#ifndef __CtEventInterface_H__
#define __CtEventInterface_H__

#include "Ct.h"
#include "CtEvent.h"
#include "CtWindowContents.h"
#include "CtWindow.h"

 /* 上位ブロックからのIF要求イベントを表すクラス(非同期で行う) */
class CtEventInterface
{
public:
	CtEventInterface() {}
	virtual ~CtEventInterface();
public:
	////////////////////////////////////// AsyncCmd //////////////////////////////////////

	// WindowTrans
	static void requestWindowCmd(CtEventWindow::WinCmd rqType, CtScreenSel screen, CtWindowID id, CtWindowContents *contents, CtWindowMain *pWin, bool bDraw, CtColorFormat Format = Format_Window);
	static void requestWindowCmd(CtEventWindow::WinCmd rqType, CtWindowID id, CtWindowContents *contents = NULL);
	static void requestWindowCmd(CtEventWindow::WinCmd rqType, CtScreenSel screen, CtWindowID id, bool bDraw = true);
	// WindowInfoAccessor
	static void requestWindowInfoAccessCmd(CtEventWinInfoAccess::WinInfoAccess rqType, CtScreenSel screen, CtWindowInfo *pinfo, CtSynchro * sync);
	static void requestWindowInfoAccessCmd(CtEventWinInfoAccess::WinInfoAccess rqType, CtScreenSel screen, bool bPermit = TRUE);
	static void requestWindowInfoAccessCmd(CtEventWinInfoAccess::WinInfoAccess rqType, CtScreenSel screen, CtWindowID id, CtWindowContents *contents, CtWindowMain *pWin, bool bDraw);
	static void requestWindowInfoAccessCmd(CtEventWinInfoAccess::WinInfoAccess rqType, CtScreenSel screen, CtWindowID id, CtWindowInfo *pinfo, CtSynchro * sync);
	// Sys
	static void requestSysCmd(unsigned long Event, SYS_EVENT_DATA data);
	// Key
	static void requestKeyCmd(CtEventKey::KeySource Source, CtEventKey::KeyCode Key, CtEventKey::KeyAction Action);
	// Touch
	static void requestTouchCmd(CtEventTouch::TouchAction tAction, short x, short y);
	// Param
	static void requestParamCmd(int t_Id, int int_Data);
	// Timer
	static void requestTimerCmd(int Uid, void* pInstance, unsigned long cycTim = 0);
	// Button
	static void requestButtonCmd(CtWidget* pWidget, CtWindowMain* pWinMain, const CtEventButton::PressType Type, const CtEventButton::ButtonTimerLevel TimLv = CtEventButton::Level_Invalid);
	static void requestButtonCmd(CtWidget* pWidget, CtWindowMain* pWinMain, const CtEventButton::ChangeState State, const CtEventButton::ButtonTimerLevel TimLv = CtEventButton::Level_Invalid);
	// Widget
	static void requestWidgetCmd(unsigned long WidgetId, CtWidget* pWidget, const CtEventWidget::Request Req);
	static void requestWidgetCmd(unsigned long WidgetId, CtWidget* pWidget, const CtEventWidget::Request Req, CtWindowMain* pWinMain);
	// DrawResult
	static void requestDrawResultCmd(CtScreenSel screen, CtWindowID id, CtWindowMain* pWin);

	////////////////////////////////////// SyncCmd //////////////////////////////////////
	// Func
	static void requestFuncCmd(CtWindowID id, CtFuncID funcId);
	static void requestFuncCmd(CtScreenSel screen, CtWindowID id, CtFuncID funcId, CtWindowContents* pContents = NULL);
	static void requestFuncCmd(CtFuncID funcId, CtWindowMain* pWin, CtWindowContents* pContents = NULL);
	static void requestFuncCmd(CtFuncID funcId, CtWindow* pWin, CtWindowContents* pContents = NULL);
};
#endif
