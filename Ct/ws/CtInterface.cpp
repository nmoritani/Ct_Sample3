#include "CtInterface.h"
#include "CtEventInterface.h"
#include "CtComMainThread.h"
#include "CtWindowMain.h"
#include "CtWindowController.h"
#include "CtSynchro.h"

CtInterface* CtInterface::m_pInstance = NULL;

CtInterface::CtInterface() :
	m_pWc(CtWindowController::getInstance())
{
	setClassType(CtClassType_Interface);
}


CtInterface::~CtInterface()
{
}

CtInterface* CtInterface::getInstance()
{
	if (!m_pInstance) {
		m_pInstance = new CtInterface();
	}
	return m_pInstance;
}

void CtInterface::changeWindow(CtScreenSel screen, CtWindowID id, CtWindowContents* contents, bool bDraw, CtColorFormat Format) const
{
	CtWindowMain *pWin = m_pWc->createWindow(screen, id, contents);

	CtDebugPrint(CtDbg, "CtInterface::changeWindow(%#x, %#010x, %p, %p, %d)\n", screen, id, contents, pWin, bDraw);
	CtDebugPrint(CtDbgIdCmd, "(%d,%d,%d,%d,%d)\n", screen, ID_WIND, CtEventWindow::Change, id, bDraw);
	CtEventInterface::requestWindowCmd(CtEventWindow::Change, screen, id, contents, pWin, bDraw, Format);
}

#if 0	// TimeStampテスト
#include "../../TimeStamp/gui_timestamp_api.h"

void ts_callback(int id)
{
}

static bool bFirst = true;
static int TsVari = 0;
static int mTsId = -1;
#define VariMax	3
#endif

void CtInterface::popupWindow(CtScreenSel screen, CtWindowID id, CtWindowContents* contents, bool bDraw) const
{
	CtWindowMain *pWin = m_pWc->createWindow(screen, id, contents);

	CtDebugPrint(CtDbg, "CtInterface::popupWindow(%#x, %#010x, %p, %p, %d)\n", screen, id, contents, pWin, bDraw);
	CtDebugPrint(CtDbgIdCmd, "(%d,%d,%d,%d,%d)\n", screen, ID_WIND, CtEventWindow::Popup, id, bDraw);
	CtEventInterface::requestWindowCmd(CtEventWindow::Popup, screen, id, contents, pWin, bDraw);

#if 0	// TimeStampテスト
	if (id == 0x04110001) {
		if (bFirst) {
			GUI_TS_FORMAT f;
			switch (TsVari) {
			case 0:
				f.rect_w = 1536;
				f.rect_h = 272;
				f.col_type = GUI_COLOR_TYPE_422;
				f.col_depth = GUI_COLOR_DEPTH_10BIT;
				f.type = GUI_TS_TYPE_DATETIME;
				break;
			case 1:
				f.rect_w = 1400;
				f.rect_h = 400;
				f.col_type = GUI_COLOR_TYPE_422;
				f.col_depth = GUI_COLOR_DEPTH_8BIT;
				f.type = GUI_TS_TYPE_DATETIME;
				break;
			case 2:
				f.rect_w = 1536;
				f.rect_h = 272;
				f.col_type = GUI_COLOR_TYPE_420;
				f.col_depth = GUI_COLOR_DEPTH_10BIT;
				f.type = GUI_TS_TYPE_TIME;
				break;
			case 3:
				f.rect_w = 800;
				f.rect_h = 200;
				f.col_type = GUI_COLOR_TYPE_422;
				f.col_depth = GUI_COLOR_DEPTH_8BIT;
				f.type = GUI_TS_TYPE_DATE;
				break;
			}
			if (TsVari < VariMax)		TsVari++;
			else						TsVari = 0;

			mTsId = GUI_CreateTimeStamp(f, ts_callback);
			CtDebugPrint(CtDbg, "[TS] GUI_CreateTimeStamp() : %d\n", mTsId);

			bFirst = false;

		}
		else {
			GUI_DestroyTimeStamp(mTsId);
			bFirst = true;
		}
	}
#endif
}

void CtInterface::swapWindow(CtScreenSel screen, CtWindowID id, CtWindowContents* contents, bool bDraw) const
{
	CtWindowMain *pWin = m_pWc->createWindow(screen, id, contents);

	CtDebugPrint(CtDbg, "CtInterface::swapWindow(%#x, %#010x, %p, %p, %d)\n", screen, id, contents, pWin, bDraw);
	CtDebugPrint(CtDbgIdCmd, "(%d,%d,%d,%d,%d)\n", screen, ID_WIND, CtEventWindow::Close, id, bDraw);
	CtEventInterface::requestWindowCmd(CtEventWindow::Swap, screen, id, contents, pWin, bDraw);
}

void CtInterface::returnWindow(CtScreenSel screen, CtWindowID id, bool bDraw) const
{
	CtDebugPrint(CtDbg, "CtInterface::returnWindow(%#x, %#010x, %d)\n", screen, id, bDraw);
	CtDebugPrint(CtDbgIdCmd, "(%d,%d,%d,%d,%d)\n", screen, ID_WIND, CtEventWindow::Return, id, bDraw);
	CtEventInterface::requestWindowCmd(CtEventWindow::Return, screen, id, bDraw);
}

void CtInterface::closeWindow(CtScreenSel screen, CtWindowID id, bool bDraw) const
{
	CtDebugPrint(CtDbg, "CtInterface::closeWindow(%#x, %#010x, %d)\n", screen, id, bDraw);
	CtDebugPrint(CtDbgIdCmd, "(%d,%d,%d,%d,%d)\n", screen, ID_WIND, CtEventWindow::Close, id, bDraw);
	CtEventInterface::requestWindowCmd(CtEventWindow::Close, screen, id, bDraw);
}

void CtInterface::removeWindow(CtScreenSel screen, CtWindowID id, bool bDraw) const
{
	CtDebugPrint(CtDbg, "CtInterface::removeWindow(%#x, %#010x, %d)\n", screen, id, bDraw);
	CtDebugPrint(CtDbgIdCmd, "(%d,%d,%d,%d,%d)\n", screen, ID_WIND, CtEventWindow::Remove, id, bDraw);
	CtEventInterface::requestWindowCmd(CtEventWindow::Remove, screen, id, bDraw);
}

CtWindowID CtInterface::getCurrentWindowID(CtScreenSel screen) const
{
	CtDebugPrint(CtDbg, "CtInterface::getCurrentWindowID Arg[ScreenSel](%#x)\n", screen);

	if (screen == ScreenAll) {
		return WindowNone;
	}

	if (CtMainThread::isOwnThread() == true) {
		if (m_pWc != NULL) {
			CtWindowMain *win = m_pWc->getCurrentWindow(toNoScreen(screen));
			if (win) {
				CtDebugPrint(CtDbg, "(CT Thread)[WindowID]%#x\n", win->getWindowID());
				return win->getWindowID();
			}
		}
	}
	else {
		CtSynchro sync;
		CtWindowInfo info;
		CtEventInterface::requestWindowInfoAccessCmd(CtEventWinInfoAccess::GetCurrentWindow, screen, &info, &sync);
		sync.wait();
		CtDebugPrint(CtDbg, "(NoneCT Thread)[WindowID]%#x\n", info.WindowID);

		return info.WindowID;
	}
	return WindowNone;
}

CtWindowID CtInterface::getRootWindowID(CtScreenSel screen) const
{
	CtDebugPrint(CtDbg, "CtInterface::%s(%#x)\n", __FUNCTION__, screen);
	if (screen == ScreenAll) {
		return WindowNone;
	}

	if (CtMainThread::isOwnThread() == true) {
		if (m_pWc != NULL) {
			CtWindowMain *win = m_pWc->getRootWindow(toNoScreen(screen));

			if (win) {
				CtDebugPrint(CtDbg, "(CT)%#x\n", win->getWindowID());
				return win->getWindowID();
			}
		}
	}
	else {
		CtSynchro sync;
		CtWindowInfo info;
		CtEventInterface::requestWindowInfoAccessCmd(CtEventWinInfoAccess::GetRootWindow, screen, &info, &sync);
		sync.wait();
		CtDebugPrint(CtDbg, "(NoneCT)%#x\n", info.WindowID);

		return info.WindowID;
	}

	return WindowNone;
}

CtWindowInfo CtInterface::getWindowInfo(CtScreenSel screen, CtWindowID id) const
{
	if (screen == ScreenAll) {
		CtWindowInfo info;
		memset(&info, 0, sizeof(info));
		info.WindowID = WindowNone;

		return info;
	}

	if (m_pWc != NULL) {
		CtWindowMain *win = m_pWc->getWindow(toNoScreen(screen), id);

		if (win) {
			return *win->getWindowInfo();
		}
	}
	// window not found
	CtWindowInfo info;
	memset(&info, 0, sizeof(info));
	return info;
}

CtWindowID CtInterface::checkDrawWindowID(CtScreenSel screen, CtWindowID id) const
{
	if (screen == ScreenAll) {
		CtDebugPrint(CtDbg, "CtInterface::checkDrawWindowID(%#x, %#010x) = Err[%d]\n", screen, id, __LINE__);
		return WindowNone;
	}
	if (id == WindowNone) {
		CtDebugPrint(CtDbg, "CtInterface::checkDrawWindowID(%#x, %#010x) = Err[%d]\n", screen, id, __LINE__);
		return WindowNone;
	}

	if (CtMainThread::isOwnThread() == true) {
		if (m_pWc != NULL) {
			CtWindowMain *win = m_pWc->getDrawWindow(toNoScreen(screen), id);
			if (win) {
				CtDebugPrint(CtDbg, "CtInterface::checkDrawWindowID(%#x, %#010x) = (CT)%#010x\n", screen, id, win->getWindowID());
				return win->getWindowID();
			}
		}
	}
	else {
		CtSynchro sync;
		CtWindowInfo info;
		CtEventInterface::requestWindowInfoAccessCmd(CtEventWinInfoAccess::checkDrawWindow, screen, id, &info, &sync);
		sync.wait();
		CtDebugPrint(CtDbg, "CtInterface::checkDrawWindowID(%#x, %#010x) = (NoneCT)%#010x\n", screen, id, info.WindowID);
		return info.WindowID;
	}
	CtDebugPrint(CtDbg, "CtInterface::checkDrawWindowID(%#x, %#010x) = WindowNone\n", screen, id);
	return WindowNone;
}

bool CtInterface::checkWindowCategory(CtWindowID WindowID)
{
	if (WindowID == WindowNone) {
		return false;
	}

	if (WindowID & 0x0000FFFF) {
		/* カテゴリーではない */
		return false;
	}
	return true;
}

bool CtInterface::checkWindowCategory(CtWindowID WindowID, CtWindowID CategoryID)
{
	bool bRet = false;

	if (checkWindowCategory(CategoryID)) {
		if ((CategoryID == (WindowID & 0xFFFF0000)) ||
			(CategoryID == (WindowID & 0xFFF00000)) ||
			(CategoryID == (WindowID & 0xFF0F0000)) ||
			(CategoryID == (WindowID & 0xFF000000)) ||
			(CategoryID == (WindowID & 0xF0FF0000)) ||
			(CategoryID == (WindowID & 0xF0F00000)) ||
			(CategoryID == (WindowID & 0xF00F0000)) ||
			(CategoryID == (WindowID & 0xF0000000)) ||
			(CategoryID == (WindowID & 0x0FFF0000)) ||
			(CategoryID == (WindowID & 0x0FF00000)) ||
			(CategoryID == (WindowID & 0x0F0F0000)) ||
			(CategoryID == (WindowID & 0x0F000000)) ||
			(CategoryID == (WindowID & 0x00FF0000)) ||
			(CategoryID == (WindowID & 0x00F00000)) ||
			(CategoryID == (WindowID & 0x000F0000))) {
			bRet = true;
		}
	}

	CtDebugPrint(CtDbg, "CtInterface::checkWindowCategory(WindowID %#010x)(CategoryID %#010x) = %s\n", WindowID, CategoryID, bRet ? "true" : "false");

	return bRet;
}

void CtInterface::setWindowContents(CtScreenSel screen, CtWindowID id, CtWindowContents *contents) const
{
	CtWindowMain *win = NULL;
	if (!win && (screen & ScreenLCD)) {
		win = m_pWc->getWindow(toNoScreen(ScreenLCD), id);
	}
	if (!win && (screen & ScreenLOUT)) {
		win = m_pWc->getWindow(toNoScreen(ScreenLOUT), id);
	}

	if (win) {
		win->setContents(contents);
		CtEventInterface::requestWindowInfoAccessCmd(CtEventWinInfoAccess::UpdateContents, screen, id, NULL, NULL, TRUE);
	}
}

void CtInterface::setEventFilter(CtWindowID id, CtEventFilter filter) const
{
	//CtDebugPrint(CtDbgIdCmd, "(%d,%d,%d,%d)\n", CtDbgCmndDomain::SCREEN_ALL, CtDbgCmndDomain::ID_APL_EVNT, CtDbgCmndDomain::ID_EVNT_FILT, filter << 16 | id);

	if (m_pWc != NULL) {
		CtWindowMain *win = m_pWc->getWindow(toNoScreen(ScreenLCD), id);

		if (win) {
			win->setEventFilter(filter);
		}
	}
}

CtEventFilter CtInterface::getEventFilter(CtWindowID id)
{
	if (m_pWc != NULL) {
		CtWindowMain *win = m_pWc->getWindow(toNoScreen(ScreenLCD), id);

		if (win) {
			return win->getEventFilter();
		}
	}
	return EventNone;
}

void CtInterface::registerWindowFunc(CtWindowID id_win, CtFuncID id_func, CtWindowFunc func) const
{
	if (m_pWc == NULL)	return;
	m_pWc->registerWindowFunc(id_win, id_func, func);
}

void CtInterface::registerWindowFunc(CtWindowFunc func) const
{
	if (m_pWc == NULL)	return;
	m_pWc->registerWindowFunc((CtWindowID)0xFFFFFFFF, FuncID_ALL, func);
}

void CtInterface::unregisterWindowFunc(CtFuncID id_func) const
{
	if (m_pWc == NULL)	return;
	m_pWc->unregisterWindowFunc(id_func);
}

void CtInterface::setNotifyFunc(CtNotifyFunc func) const
{
	if (m_pWc == NULL)	return;
	m_pWc->setNotifyFunc(func);
}

void CtInterface::setScreen(CtScreenSel screen) const
{
	CtEventInterface::requestWindowInfoAccessCmd(CtEventWinInfoAccess::SetScreen, screen);
}

CtScreenSel CtInterface::getScreen(void) const
{
	if (m_pWc == NULL)	return ScreenNone;
	return m_pWc->getScreen();
}

CtScreenInfo CtInterface::getScreenInfo(CtScreenSel screen) const
{
	return CtDraw::getInstance()->getScreenInfo(screen);
}

void CtInterface::permitTransition(bool isAutoTrans) const
{
}

void CtInterface::permitDrawing(CtScreenSel screen, bool isDrawing) const
{
}

void CtInterface::putRopEvent(CtEventKey::KeyCode Key, CtEventKey::KeyAction Action)
{
	// KeyEventと同様
	CtEventInterface::requestKeyCmd(CtEventKey::KeySource_Controller, Key, Action);
}

void CtInterface::outputWindowOutline(CtScreenSel Sel, CtWindowID id) const
{
	CtWindowMain* pWin = NULL;
	int Screen;

	if (m_pWc == NULL) return;

	for (Screen = 0; Screen < CT_SCREEN_NUM; Screen++) {
		if ((Sel & toSelScreen(Screen)) && ((pWin = m_pWc->getCurrentWindow(Screen)) != NULL))
			pWin->outputOutline(Screen);
	}
}

