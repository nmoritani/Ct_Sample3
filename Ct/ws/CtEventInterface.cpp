/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtEventInterface
 */

#include "CtEventInterface.h"
#include "CtWindowController.h"
#include "CtWindowMain.h"

// デストラクタ
CtEventInterface::~CtEventInterface(){
}

void CtEventInterface::requestWindowCmd(CtEventWindow::WinCmd rqType, CtScreenSel screen, CtWindowID id, CtWindowContents *contents, CtWindowMain *pWin, bool bDraw, CtColorFormat Format) {
	CtEvent* event = new CtEventWindow(rqType, screen, id, contents, pWin, bDraw, Format);	/* pgr0541 */
	event->send();
}

void CtEventInterface::requestWindowCmd(CtEventWindow::WinCmd rqType, CtWindowID id, CtWindowContents *contents) {
	CtEvent* event = new CtEventWindow(rqType, id, contents);	/* pgr0541 */
	event->send();
}

void CtEventInterface::requestWindowCmd(CtEventWindow::WinCmd rqType, CtScreenSel screen, CtWindowID id, bool bDraw) {
	CtEvent* event = new CtEventWindow(rqType, screen, id, bDraw);
	event->send();
}

void CtEventInterface::requestWindowInfoAccessCmd(CtEventWinInfoAccess::WinInfoAccess rqType, CtScreenSel screen, CtWindowInfo *pinfo, CtSynchro * sync) {
	CtEvent* event = new CtEventWinInfoAccess(rqType, screen, pinfo, sync);	/* pgr0541 */
	event->send();
}
void CtEventInterface::requestWindowInfoAccessCmd(CtEventWinInfoAccess::WinInfoAccess rqType, CtScreenSel screen, bool bPermit) {
	CtEvent* event = new CtEventWinInfoAccess(rqType, screen, bPermit);
	event->send();
}

void CtEventInterface::requestWindowInfoAccessCmd(CtEventWinInfoAccess::WinInfoAccess rqType, CtScreenSel screen, CtWindowID id, CtWindowContents *contents, CtWindowMain *pWin, bool bDraw) {
	CtEvent* event = new CtEventWinInfoAccess(rqType, screen, id, contents, pWin, bDraw);	/* pgr0541 */
	event->send();
}
void CtEventInterface::requestWindowInfoAccessCmd(CtEventWinInfoAccess::WinInfoAccess rqType, CtScreenSel screen, CtWindowID id, CtWindowInfo *pinfo, CtSynchro * sync) {
	CtEvent* event = new CtEventWinInfoAccess(rqType, screen, id, pinfo, sync);	/* pgr0541 */
	event->send();
}
void CtEventInterface::requestSysCmd(unsigned long Event, SYS_EVENT_DATA data) {
	CtEvent* event = new CtEventSys(Event, data);
	event->send();
}

void CtEventInterface::requestKeyCmd(CtEventKey::KeySource Source, CtEventKey::KeyCode Key, CtEventKey::KeyAction Action) {
	CtEvent* event = new CtEventKey(Action, Key, Source);
	event->send();
}

void CtEventInterface::requestTouchCmd(CtEventTouch::TouchAction tAction, short x, short y) {
	CtEvent* event = new CtEventTouch(tAction, x, y);
	event->send();
}

void CtEventInterface::requestParamCmd(int t_Id, int int_Data) {
	CtEvent* event = new CtEventParam(t_Id, int_Data);
	event->send();
}

void CtEventInterface::requestTimerCmd(int Uid, void* pInstance, unsigned long cycTim) {
	CtEvent* event = new CtEventTimer(Uid, pInstance, cycTim);	/* pgr0541 */
	event->send();
}

void CtEventInterface::requestButtonCmd(CtWidget* pWidget, CtWindowMain* pWinMain, const CtEventButton::PressType Type, const CtEventButton::ButtonTimerLevel TimLv) {
	CtEvent* event = new CtEventButton(pWidget->getWidgetID(), pWidget, pWinMain, Type,TimLv);	/* pgr0541 */
	event->send();
}

void CtEventInterface::requestButtonCmd(CtWidget* pWidget, CtWindowMain* pWinMain, const CtEventButton::ChangeState State, const CtEventButton::ButtonTimerLevel TimLv) {
	CtEvent* event = new CtEventButton(pWidget->getWidgetID(), pWidget, pWinMain, State, TimLv);	/* pgr0541 */
	event->send();
}

void CtEventInterface::requestWidgetCmd(unsigned long WidgetId, CtWidget* pWidget, const CtEventWidget::Request Req) {
	CtEvent* event = new CtEventWidget(WidgetId, pWidget, Req, pWidget->getMain());	/* pgr0541 */
	event->send();
}

void CtEventInterface::requestWidgetCmd(unsigned long WidgetId, CtWidget* pWidget, const CtEventWidget::Request Req, CtWindowMain* pWinMain) {
	CtEvent* event = new CtEventWidget(WidgetId, pWidget, Req, pWinMain);	/* pgr0541 */
	event->send();
}

void CtEventInterface::requestDrawResultCmd(CtScreenSel screen, CtWindowID id, CtWindowMain* pWinMain) {
	CtEvent* event = new CtEventDrawResult(screen, id, pWinMain);	/* pgr0541 */
	event->send();
}

////////////////////////////////////// SyncCmd //////////////////////////////////////
void CtEventInterface::requestFuncCmd(CtWindowID id, CtFuncID funcId) {
	CtEventFunc(ScreenAll, id, funcId, NULL).exec();
}

void CtEventInterface::requestFuncCmd(CtScreenSel screen, CtWindowID id, CtFuncID funcId, CtWindowContents* pContents) {
	CtEventFunc(screen, id, funcId, pContents).exec();
}

void CtEventInterface::requestFuncCmd(CtFuncID funcId, CtWindowMain* pWinMain, CtWindowContents* pContents) {
	if (pWinMain == NULL) return;
	CtEventFunc(pWinMain->getScreenSel(), pWinMain->getWindowID(), funcId, pContents).exec();
}

void CtEventInterface::requestFuncCmd(CtFuncID funcId, CtWindow* pWin, CtWindowContents* pContents) {
	if (pWin == NULL) return;
	CtEventFunc(pWin->getScreenSel(), pWin->getWindowID(), funcId, pContents).exec();
}
