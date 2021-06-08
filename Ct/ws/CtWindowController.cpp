/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindowController
 */

#include "CtDebugPrint.h"
#include "CtWindowController.h"
#include "CtWindowFactory.h"
#include "CtWindowIDString.h"
#include "CtVector.h"
#include "CtDrawTask.h"
#include "CtWindowList.h"
#include "CtWindowContents.h"
#include "CtWindowMain.h"
#include "CtObserverParamService.h"
#include "CtSynchro.h"
#include "CtEventInterface.h"
#include "AplParamService.h"
#include "CtSysEventTranslator.h"
#include "CtDrawCache.h"

#include "CtTimeMesure.h"

#ifndef WIN32_GUI_SIM
#include "guiif_avc.h"
#include "gui_main.h"
#endif

CtWindowController* CtWindowController::m_pInstance = NULL;
CtColorFormat CurrentFormat = Format_RGBA4444;

CtWindowController::CtWindowController() :
	m_pDraw(CtDraw::getInstance()),
	m_pTimer(CtTimer::getInstance()),
	m_pParamIf(new CtObserverParamService()),
	m_ScreenOut(ScreenAll),	// 暫定対応:本来はScreenNoneが正しい
	m_bBanFrameOperation(true),
	m_Notify(NULL)
{
	setClassType(CtClassType_WindowController);

	for (int Screen = 0; Screen < CT_SCREEN_NUM; Screen++) {
		m_WindowList[Screen] = new CtWindowList(m_PopupWindowLimit, m_ChangeWindowLimit);
		m_VisiblePos[Screen] = 0;
	}
	memset(m_FuncList, 0x00, sizeof(m_FuncList));
	CtSysEventTranslator::getInstance();
	CtRegion initRegion(0, 0, 0, 0);
	m_Invalidates.reserve(128);
	for (int i = 0; i < m_Invalidates.capacity(); i++) {
		m_Invalidates[i] = initRegion;
	}
	m_InvalidatesFast.reserve(128);
	for (int i = 0; i < m_InvalidatesFast.capacity(); i++) {
		m_InvalidatesFast[i] = initRegion;
	}
}

CtWindowController::~CtWindowController()
{
	// リスト内のWindowとリスト実体の破棄
	for (int Screen = 0; Screen < CT_SCREEN_NUM; Screen++) {
		if (m_WindowList[Screen] != NULL)	delete m_WindowList[Screen];
	}

	if (m_pDraw != NULL)			delete m_pDraw;
	if (m_pParamIf != NULL)			delete m_pParamIf;

	CtWindowFactory::Destroy();
}

CtWindowController* CtWindowController::getInstance() {
	if (!m_pInstance) {
		m_pInstance = new CtWindowController();
	}
	return m_pInstance;
}

void CtWindowController::putEvent(CtEvent& Event)
{
	if (Event.exec() != true)
		return;
}

bool CtWindowController::WindowEvent(const CtEventWindow& Event)
{
	bool res[CT_SCREEN_NUM] = { false };
	CtWindowMain* pWindow[CT_SCREEN_NUM] = { NULL };
	CtWindowMain* pOldTop[CT_SCREEN_NUM] = { NULL };
	CtEventWindow::WindowArgs arg = Event.getArgs();

	banFrameOperation(true);

	for (int Screen = 0; Screen < CT_SCREEN_NUM; Screen++) {	// Window重畳変化をチェック
		CtWindowList* pList = getWindowList(Screen);
		pWindow[Screen] = pList->get(CtWindowList::Current);
		if (m_Current[Screen].size() > 0)
			pOldTop[Screen] = m_Current[Screen][m_Current[Screen].size() -1];
	}

	if ((Event.getEventType() == CtEventWindow::Change) &&
		((arg.Format == Format_RGBA4444) || (arg.Format == Format_RGBA8888))) {
		bool flag = true;
		for (int Screen = 0; Screen < CT_SCREEN_NUM; Screen++) {
			if (getRootWindow(Screen) != NULL) {
				flag = false;
			}
		}
		if ((flag == true) && (arg.Format != m_pDraw->getScreenInfo(0).Format)) {
			m_pDraw->deleteWorld();
			m_pDraw->createWorld(arg.Format);
		}
	}

	// Windowが追加される場合は、WindowListに追加可能かチェック。ダメなら通知だけして終わる
	switch (Event.getEventType()) {
	case CtEventWindow::Change:
	case CtEventWindow::Popup:
	case CtEventWindow::Swap:
		for (int i = 0; i < m_CurrentAll.size(); i++) {
			if (m_CurrentAll[i] == NULL) continue;
			if (m_CurrentAll[i]->getWindowID() == arg.id) {
				delete arg.pWindow;
				goto end;
			}
		}
		break;
	case CtEventWindow::Return:
	case CtEventWindow::Close:
	case CtEventWindow::Remove:
		break;
	default:
		goto end;
	}

	// Screen毎に実施が必要な処理
	for (int Screen = 0; Screen < CT_SCREEN_NUM; Screen++) {
		res[Screen] = NULL;
		if (!(toSelScreen(Screen) & arg.screen)) continue;

		/// 処理実施
		switch (Event.getEventType()) {
		case CtEventWindow::Change:
			res[Screen] = changeWindow(Screen, arg.id, arg.pContents, arg.pWindow, arg.bDraw);
			break;
		case CtEventWindow::Popup:
			res[Screen] = popupWindow(Screen, arg.id, arg.pContents, arg.pWindow, arg.bDraw);
			break;
		case CtEventWindow::Swap:
			res[Screen] = swapWindow(Screen, arg.id, arg.pContents, arg.pWindow, arg.bDraw);
			pOldTop[Screen] = NULL;
			break;
		case CtEventWindow::Return:
			res[Screen] = returnWindow(Screen, arg.id, arg.bDraw);
			pOldTop[Screen] = NULL;
			break;
		case CtEventWindow::Close:
			res[Screen] = closeWindow(Screen, arg.id, arg.bDraw);
			pOldTop[Screen] = NULL;
			break;
		case CtEventWindow::Remove:
			res[Screen] = removeWindow(Screen, arg.id, arg.bDraw);
			pOldTop[Screen] = NULL;
			break;
		default:
			goto end;
		}

		if ((Screen == 0) && (res[Screen] == true)) {
			if ((m_Current[0].empty() != true) && (m_Current[0][m_Current[0].size() - 1] != NULL)) {
				m_Current[0][m_Current[0].size() - 1]->cancelPressing();
			}
		}
	}

	// WindowListのキャッシュを更新する
	m_CurrentAll.clear();
	for (int Screen = 0; Screen < CT_SCREEN_NUM; Screen++) {
		m_Current[Screen].clear();

		CtWindowList *pList = getWindowList(Screen);
		const CtList::list<WindowList> &winlist = pList->getWidnowList();
		CtList::list<WindowList>::const_iterator itr;
		WindowList List;
		CtWindowMain *pWindow = NULL;
		int pos;

		m_VisiblePos[Screen] = getDrawStart(Screen);

		for (pos = 0, itr = winlist.begin(); itr != winlist.end(); ++itr, ++pos) {
			List = *itr;
			pWindow = *List.begin();
			if (pWindow == NULL) continue;

			if (pWindow->isAlive() != true)
				pWindow->startup();

			m_Current[Screen].push_back(pWindow);

			if (m_CurrentAll.find(pWindow) != true) {
				m_CurrentAll.push_back(pWindow);
			}
		}
		CtWindowDecorate::requestDecorate(&m_Current[Screen], Screen);
	}

	for (int Screen = 0; Screen < CT_SCREEN_NUM; Screen++) {
		CtWindowMain* pTop = NULL;
		if ((m_Current[Screen].size() > 0) && (pTop = m_Current[Screen][m_Current[Screen].size() -1]) != NULL) {
			if (pWindow[Screen] != pTop) {
				pTop->putWidgetEvent(CtEventWidget(0, NULL, CtEventWidget::ToFrontSide, pTop));
			}
		}
		
		if (pOldTop[Screen] != NULL) {
			if (pOldTop[Screen] != pTop) {
				pOldTop[Screen]->putWidgetEvent(CtEventWidget(0, NULL, CtEventWidget::ToBackSide, pOldTop[Screen]));
			}
		}
	}
	
	for (int Screen = 0; Screen < CT_SCREEN_NUM; Screen++) {
		CtWindowList* pList = getWindowList(Screen);
		if ((pWindow[Screen] != NULL) && (pList->get(CtWindowList::Current) == NULL)) {
			clearScreen(Screen, 0);
		}
		else {
			drawScreen(Screen, 0);
		}
	}

end:
	banFrameOperation(false);

	if (!m_Notify) return true;

	// 結果通知
	for (int Screen = 0; Screen < CT_SCREEN_NUM; Screen++) {
		if (!(toSelScreen(Screen) & arg.screen)) continue;

		CtWindowMain* pWindow;
		CtWindowID id = WindowNone;
		CtNotifyType type = CtNotifyError;
		int err = -1;

		if (res[Screen]) {
			if ((m_Current[Screen].size() >= 1) &&
				((pWindow = m_Current[Screen][m_Current[Screen].size() - 1]) != NULL)) {
				id = pWindow->getWindowInfo()->WindowID;
			}
			type = CtNotifyTransitionComplete;
			err = 0;
		}

		//CtDebugPrint(CtDbg, "CtWindowController::m_Notify(%#x, %#x, %#x)\n", id, type, err);
		m_Notify(toSelScreen(Screen), id, type, (void*)err);
	}

	return true;
}

bool CtWindowController::WinInfoEvent(const CtEventWinInfoAccess& Event)
{
	CtEventWinInfoAccess::WinInfoArgs arg = Event.getArgs();
	// 全Screenで1度のみ実施すればよい、またはAll非対応の処理
	switch (Event.getEventType()) {
	case CtEventWinInfoAccess::UpdateContents:
		if (updateContents(arg.WinInfoCnts.screen, arg.WinInfoCnts.id) != true)
			return false;

		for (int Screen = 0; Screen < CT_SCREEN_NUM; Screen++) {
			drawScreen(Screen, 0);
		}
		return true;

	case CtEventWinInfoAccess::GetRootWindow:
	case CtEventWinInfoAccess::GetCurrentWindow:
	{
		CtWindowMain *win;
		CtWindowInfo *pInfo = arg.WindowInfoArgs.pWindowInfo;
		CtSynchro    *pSync = arg.WindowInfoArgs.pSynchro;
		int			  screen = toNoScreen(arg.WindowInfoArgs.screen);

		win = (Event.getEventType() == CtEventWinInfoAccess::GetRootWindow) ? getRootWindow(screen) : getCurrentWindow(screen);

		if (pInfo) {
			if (win) {
				*pInfo = *win->getWindowInfo();
			}
			else {
				pInfo->ScreenSel = ScreenNone;
				pInfo->WindowID = WindowNone;
			}
		}

		if (pSync) {
			pSync->notify();
		}
	}
	return false;

	case CtEventWinInfoAccess::PermitDrawing: {
		return false;
	}
	case CtEventWinInfoAccess::checkDrawWindow: {
		CtWindowMain *win;
		CtWindowID   id = arg.WindowDorwInfoArgs.id;
		CtWindowInfo *pInfo = arg.WindowDorwInfoArgs.pWindowInfo;
		CtSynchro    *pSync = arg.WindowDorwInfoArgs.pSynchro;
		int			 screen = toNoScreen(arg.WindowDorwInfoArgs.screen);

		win = getDrawWindow(screen, id);

		if (pInfo) {
			if (win) {
				*pInfo = *win->getWindowInfo();
			}
			else {
				pInfo->ScreenSel = ScreenNone;
				pInfo->WindowID = WindowNone;
			}
		}
		if (pSync) {
			pSync->notify();
		}
		return false;
	}
	default:
		return false;
		break;
	}
}

bool CtWindowController::KeyEvent(const CtEventKey& Key)
{
	//	CtDebugPrint(CtDbg, "keyAction = %d, keyCode = %d, keySource = %d\n", Key.getKeyAction(), Key.getKeyCode(), Key.getKeySource());

	if ((m_Current[0].empty() == true) || (m_Current[0][m_Current[0].size() - 1] == NULL))
		return false;

	if (m_Current[0][m_Current[0].size() - 1]->putKeyEvent(Key) != true)
		return false;

	for (int Screen = 0; Screen < CT_SCREEN_NUM; Screen++) {
		drawScreen(Screen, 0);
	}
	return true;
}

bool CtWindowController::TouchEvent(const CtEventTouch& Touch)
{
	if ((m_Current[0].empty() == true) || (m_Current[0][m_Current[0].size() - 1] == NULL))
		return false;

	if (m_Current[0][m_Current[0].size() - 1]->putTouchEvent(Touch) != true)
		return false;

	for (int Screen = 0; Screen < CT_SCREEN_NUM; Screen++) {
		drawScreen(Screen, 0);
	}
	return true;
}

bool CtWindowController::TimerEvent(const CtEventTimer& Timer)
{
	if (static_cast<CtEventHandler*>(Timer.getInstance())->handleTimerEvent(Timer) != true)
		return false;

	for (int Screen = 0; Screen < CT_SCREEN_NUM; Screen++) {
		drawScreen(Screen, 0);
	}
	return true;
}

bool CtWindowController::ParamEvent(const CtEventParam& Param)
{
	bool bRet = false;
	CtDebugPrint(CtDbg, "%s(Id:%d, Val:%d)\n", __FUNCTION__, Param.getParamId(), Param.getParamVal());
	for (int i = 0; i < m_CurrentAll.size(); i++) {
		if (m_CurrentAll[i] == NULL)	continue;

		if (m_CurrentAll[i]->putParamEvent(Param) == true)
			bRet = true;
	}
	if (bRet != true)
		return false;

	for (int Screen = 0; Screen < CT_SCREEN_NUM; Screen++) {
		drawScreen(Screen, 0);
	}
	return true;
}

bool CtWindowController::FlashEvent(const CtEventFlash& Flash)
{
	bool bRet = false;

	for (int i = 0; i < m_CurrentAll.size(); i++) {
		if (m_CurrentAll[i] == NULL)	continue;

		if (m_CurrentAll[i]->putFlashEvent(Flash) == true)
			bRet = true;
	}
	if (bRet != true)
		return false;

	for (int Screen = 0; Screen < CT_SCREEN_NUM; Screen++) {
		drawScreen(Screen, 0);
	}
	return true;
}


bool CtWindowController::ButtonEvent(const CtEventButton& Button)
{
	bool bRet = false;
	CtWindowMain* pWindow = NULL;

	if (m_Current[0].empty() == true)
		return false;

	for (int i = 0; i < m_CurrentAll.size(); i++) {
		if ((pWindow = m_CurrentAll[i]) == NULL) continue;
		if (pWindow != Button.getWinMain()) continue;

		if (pWindow->putButtonEvent(Button) == true)
			bRet = true;
	}

	if (bRet != true)
		return false;
	
	for (int Screen = 0; Screen < CT_SCREEN_NUM; Screen++) {
		drawScreen(Screen, 0);
	}
	
	return true;
}

bool CtWindowController::WidgetEvent(const CtEventWidget& Widget)
{
	bool bRet = false;
	CtWindowMain* pWindow = NULL;
	
	if ((pWindow = Widget.getWinMain()) == NULL) {
		return false;
	}

	if (m_CurrentAll.find(pWindow) == false) {
		return false;
	}
	
	banFrameOperation(true);
	if ((bRet = pWindow->putWidgetEvent(Widget)) == true) {
		for (int Screen = 0; Screen < CT_SCREEN_NUM; Screen++) {
			drawScreen(Screen, 0);
		}
	}
	banFrameOperation(false);

	return bRet;;
}

bool CtWindowController::FuncEvent(const CtEventFunc& Event)
{
	CtEventFunc::FuncArgs funcArgs = Event.getArgs();
	return notifyWindowFunc(funcArgs.screen, funcArgs.id, funcArgs.funcId, funcArgs.pContents);
}

bool CtWindowController::DrawResultEvent(const CtEventDrawResult& Event)
{
	CtEventDrawResult::DrawArgs drawArgs = Event.getArgs();

	if (drawArgs.pWinMain != NULL) {
		for (int i = 0; i < m_CurrentAll.size(); i++) {
			if ((m_CurrentAll[i] == NULL) || (m_CurrentAll[i]->isAlive() != true))	continue;
			if (m_CurrentAll[i] == drawArgs.pWinMain)
				return drawArgs.pWinMain->putDrawResult(Event);
		}

	}
	else {
		if ((m_Current[0].empty() == true) || (m_Current[0][m_Current[0].size() - 1] == NULL))
			return false;

		return m_Current[0][m_Current[0].size() - 1]->putDrawResult(Event);
	}
	return true;
}

bool CtWindowController::RequestEvent(const CtEventRequest& Request)
{
	if ((m_Current[0].empty() == true) || (m_Current[0][m_Current[0].size() - 1] == NULL))
		return false;

	if (m_Current[0][m_Current[0].size() - 1]->putRequestEvent(Request) != true)
		return false;

	for (int Screen = 0; Screen < CT_SCREEN_NUM; Screen++) {
		drawScreen(Screen, 0);
	}
	return true;
}

bool CtWindowController::handleFrameSync(unsigned long FrameCount)
{
	if (m_bBanFrameOperation == true)
		return false;
	if (m_pDraw->getDrawing(false) != true)
		return false;

	for (int i = 0; i < m_CurrentAll.size(); i++) {
		if ((m_CurrentAll[i] == NULL) || (m_CurrentAll[i]->isAlive() != true))	continue;
		m_CurrentAll[i]->updateFastDraw(FrameCount);
	}

	for (int Screen = 0; Screen < CT_SCREEN_NUM; Screen++) {
#ifdef WIN32_GUI_SIM
		drawScreenFast(Screen);
		m_pDraw->updateScreen(Screen);
#else
		if (GUIAVC_isUpdateEnable((GUIAVC_DISP_ID)Screen) == TRUE) {
			drawScreenFast(Screen);
			m_pDraw->updateScreen(Screen);
		}
		else {
			//smDebugPrintf(CtLog, "[%s] Screen = %d Error\n", __FUNCTION__, Screen);
		}
#endif
	}

	for (int i = 0; i < m_CurrentAll.size(); i++) {
		if ((m_CurrentAll[i] == NULL) || (m_CurrentAll[i]->isAlive() != true))	continue;

		if ((m_CurrentAll[i]->isDrawing(0) == true) || (m_CurrentAll[i]->isDrawing(1) == true)) {
			// drawingからviwingになったWindowMainは全部送ること
			CtEventInterface::requestDrawResultCmd(ScreenAll, m_CurrentAll[i]->getWindowID(), m_CurrentAll[i]);
		}
	}

	m_pDraw->freeDrawing(false);
	return true;
}



bool CtWindowController::clearScreen(int Screen, int delay)
{
	CtWindowList *pList = NULL;
#if 0
	// delay付きのpaintにすること
	if (delay != 0) {
		CtTimer::setAram(0, delay, this);
		return false;
	}
#endif
	if (m_pDraw->getDrawing(true) == true) {
		m_pDraw->clearScreen(Screen);
		m_pDraw->freeDrawing(true);
	}

	return true;
}

bool CtWindowController::drawScreen(int Screen, int delay)
{
	CtWindowMain *pWindow = NULL;
	CtVector::Vector<CtWindowMain*> Currents;

#if 0
	// delay付きのpaintにすること
	if (delay != 0) {
		CtTimer::setAram(0, delay, this);
		return false;
	}
#endif
	if (m_Current[Screen].empty() == true)
		return false;

	if (m_pDraw->getDrawing(true) == true) {
		m_VisiblePos[Screen] = getDrawStart(Screen);
		for (int i = m_VisiblePos[Screen]; i < m_Current[Screen].size(); i++) {
			if ((pWindow = m_Current[Screen][i]) == NULL)
				continue;

			pWindow->getInvalidates(m_Invalidates, Screen);
			Currents.push_back(pWindow);
		}

		if (m_Invalidates.empty() == true)
			goto exit;

		m_pDraw->drawScreen(&Currents, &m_Invalidates, Screen);
		m_Invalidates.clear();
	}

exit:
	m_pDraw->freeDrawing(true);

	return true;
}

bool CtWindowController::drawScreenFast(int Screen)
{
	CtWindowMain *pWindow = NULL;
	CtVector::Vector<CtWindowMain*> Currents;

	if (m_Current[Screen].empty() == true)
		return false;

	for (int i = m_VisiblePos[Screen]; i < m_Current[Screen].size(); i++) {
		pWindow = m_Current[Screen][i];
		if (pWindow == NULL) {
			continue;
		}
		else if ((pWindow->isAlive() != true)) {
			continue;
		}

		pWindow->getInvalidatesFast(m_InvalidatesFast, Screen);
		Currents.push_back(pWindow);
	}

	if (m_InvalidatesFast.empty() == true)
		return false;

	m_pDraw->drawScreenFast(&Currents, &m_InvalidatesFast, Screen);
	m_InvalidatesFast.clear();

	return true;
}

bool CtWindowController::changeWindow(int Screen, CtWindowID id, CtWindowContents* contents, CtWindowMain* pWindow, bool bUpdate)
{
	/// 画面を差し替える
	CtDebugPrint(CtDbg, "CtWindowController::changeWindow(%#x, %#010x, %s, %p, %d)\n", Screen, id, CtWindowIDString::getString(id), contents, bUpdate);

	if (!pWindow) return false;

	CtWindowList* pList = getWindowList(Screen);
	if (!pList) return false;

	CtScreenSel Sel = toSelScreen(Screen);

	if (pWindow->haveWindow(Sel) == false) {
		pWindow->create(Sel);
	}

	if (!pList->changeWindow(pWindow)) {
		destroyWindow(Sel, pWindow);
		return false;
	}

	if (bUpdate) {
		pWindow->setInvalidate();
	}

	return true;
}

bool CtWindowController::popupWindow(int Screen, CtWindowID id, CtWindowContents* contents, CtWindowMain* pWindow, bool bUpdate)
{
	/// 画面をポップアップ
	CtDebugPrint(CtDbg, "CtWindowController::popupWindow(%#x, %#010x, %s, %p, %d)\n", Screen, id, CtWindowIDString::getString(id), contents, bUpdate);

	if (!pWindow) return false;

	CtWindowList* pList = getWindowList(Screen);
	if (!pList) return false;

	CtScreenSel Sel = toSelScreen(Screen);

	if (pWindow->haveWindow(Sel) == false) {
		pWindow->create(Sel);
	}

	if (!pList->popupWindow(pWindow)) {
		destroyWindow(Sel, pWindow);
		return false;
	}

	if (bUpdate) {
		pWindow->setInvalidate();
	}

	return true;
}

bool CtWindowController::swapWindow(int Screen, CtWindowID id, CtWindowContents* contents, CtWindowMain* pWindow, bool bUpdate)
{
	/// カレントと画面を差し替える
	CtDebugPrint(CtDbg, "CtWindowController::swapWindow(%#x, %#010x, %s, %p, %d)\n", Screen, id, CtWindowIDString::getString(id), contents, bUpdate);

	if (!pWindow) return false;

	CtWindowList* pList = getWindowList(Screen);
	if (!pList) return false;

	CtScreenSel Sel = toSelScreen(Screen);
	CtWindowMain *pNewWindow = pWindow;
	CtWindowMain *pCurWindow = NULL;

	// 現在のカレント取得
	pCurWindow = pList->get(CtWindowList::Current);

	// 作ってなかったら作る
	if (pNewWindow->haveWindow(Sel) == false) {
		pNewWindow->create(Sel);
	}

	// 登録に失敗したらデリートする
	if (!pList->swapWindow(pNewWindow)) {
		destroyWindow(Sel, pNewWindow);
	}

	// CurWindowが存在したら置き換えているのでデリートする
	if (pCurWindow != NULL) {
		destroyWindow(Sel, pCurWindow);
	}

	if (bUpdate) {
		pNewWindow->setInvalidate();
	}

	return true;
}

bool CtWindowController::returnWindow(int Screen, CtWindowID id, bool bUpdate)
{
	/// return動作
	/// 前のWindowに戻る
	CtDebugPrint(CtDbg, "CtWindowController::returnWindow(%#x, %#010x, %s, %d)\n", Screen, id, CtWindowIDString::getString(id), bUpdate);

	CtWindowList* pList = getWindowList(Screen);
	CtWindowMain* pWindow = NULL;
	int top, tail;
	CtScreenSel Sel = toSelScreen(Screen);

	if (!pList) return false;

	// カレント位置確認
	if (!(pWindow = pList->get(CtWindowList::Current, top, tail))) {
		return false;
	}

	if (CtInterface::checkWindowCategory(id)) {
		// 対象Windowまで戻る
		const CtList::list<WindowList> &winlist = pList->getWidnowList();
		CtList::list<WindowList>::const_iterator Itr;
		WindowList::const_iterator itr;
		CtWindowMain *pWindow = NULL;

		// リスト後方(前面のCtWindow)から対象Windowを探す
		Itr = winlist.end();
		for (int i = winlist.size(); i > 0; i--) {
			Itr--;
			for (itr = (*Itr).begin(); itr != (*Itr).end(); ++itr) {
				if ((pWindow = *itr) == NULL) break;

				if (CtInterface::checkWindowCategory(pWindow->getWindowID(), id)) {
					// 対象Windowまで戻る
					returnWindow(Screen, pWindow->getWindowID(), false);
					goto End;
				}
			}
		}
	End:
		;
	}
	else if (id == WindowNone) {
		/// ひとつ前のWindowに戻る
		if (!pList->returnWindow()) return false;
		destroyWindow(Sel, pWindow);
	}
	else if (id == Window_NULL) {
		/// 全てのWindowを閉じる
		for (int i = 0; i < top + 1; i++) {
			closeWindow(Screen, WindowNone, false);
		}
	}
	else {
		/// 指定されたCtWindowIDに戻る
		int cur_top = top;

		// 指定IDの位置
		if (!(pWindow = pList->get(id, top, tail))) {
			return false;
		}

		// pWindowよりもtop側にあるCtWindowをclose
		for (int i = 0; i < cur_top - top; i++) {
			closeWindow(Screen, WindowNone, false);
		}

		// 指定IDの位置までreturn繰り返し
		for (int i = 0; i < tail; i++) {
			returnWindow(Screen, WindowNone, false);
		}
	}

	// 画面更新
	if (bUpdate) {
		pWindow = pList->get(CtWindowList::Current);
		if (pWindow) {
			pWindow->setInvalidate();
		}
	}

	return true;
}

bool CtWindowController::closeWindow(int Screen, CtWindowID id, bool bUpdate)
{
	/// Close動作
	CtDebugPrint(CtDbg, "CtWindowController::closeWindow(%#x, %#010x, %s, %d)\n", Screen, id, CtWindowIDString::getString(id), bUpdate);

	int top, tail;
	CtWindowMain *pWindow;
	CtWindowList *pList = getWindowList(Screen);
	CtVector::Vector<CtWindowMain*> deleteList;
	CtScreenSel Sel = toSelScreen(Screen);

	if (!pList) return false;

	// 指定したWindowidを含む階層を閉じる

	if (CtInterface::checkWindowCategory(id)) {
		// 対象階層をすべて閉じる

		for (int i = 0; i < m_PopupWindowLimit * m_ChangeWindowLimit; i++) {
			const CtList::list<WindowList> &winlist = pList->getWidnowList();
			CtList::list<WindowList>::const_iterator Itr;
			WindowList::const_iterator itr;
			CtWindowMain *pWindow = NULL;

			for (Itr = winlist.begin(); Itr != winlist.end(); ++Itr) {
				for (itr = (*Itr).begin(); itr != (*Itr).end(); ++itr) {
					if ((pWindow = *itr) == NULL) break;

					if (CtInterface::checkWindowCategory(pWindow->getWindowID(), id)) {
						// 対象階層を閉じ、再度対象Windowがないか確認を行う
						closeWindow(Screen, pWindow->getWindowID(), false);
						goto ConfirmAgain;
					}
				}
			}
			break;
		ConfirmAgain:	//goto
			continue;
		}
	}
	else {
		if (id == WindowNone) {
			// WindowNoneはカレントWindow
			if (!(pWindow = pList->get(CtWindowList::Current))) {
				return false;
			}
			id = pWindow->getWindowID();
		}

		if (!(pWindow = pList->get(id, top, tail))) {
			return false;
		}

		for (int i = 0; i < m_ChangeWindowLimit; i++) {
			if (!(pWindow = pList->get(top, i))) break;
			deleteList.push_back(pWindow);
		}

		pList->closeWindow(id);

		for (int i = 0; i < deleteList.size(); i++) {
			if (deleteList[i] != NULL)
				destroyWindow(Sel, deleteList[i]);
		}
	}

	// 画面更新
	if (bUpdate) {
		pWindow = pList->get(CtWindowList::Current);
		if (pWindow) {
			pWindow->setInvalidate();
		}
	}

	return true;
}

bool CtWindowController::removeWindow(int Screen, CtWindowID id, bool bUpdate)
{
	/// remove動作
	/// 指定Windowの削除
	CtDebugPrint(CtDbg, "CtWindowController::removeWindow(%#x, %#010x, %s, %d)\n", Screen, id, CtWindowIDString::getString(id), bUpdate);

	CtWindowList* pList = getWindowList(Screen);
	CtWindowMain* pWindow = NULL;
	CtScreenSel Sel = toSelScreen(Screen);
	//int top, tail;

	if (!pList) return false;

	if (CtInterface::checkWindowCategory(id)) {
		// 対象階層をすべて閉じる

		for (int i = 0; i < m_PopupWindowLimit * m_ChangeWindowLimit; i++) {
			const CtList::list<WindowList> &winlist = pList->getWidnowList();
			CtList::list<WindowList>::const_iterator Itr;
			WindowList::const_iterator itr;
			CtWindowMain *pWindow = NULL;

			for (Itr = winlist.begin(); Itr != winlist.end(); ++Itr) {
				for (itr = (*Itr).begin(); itr != (*Itr).end(); ++itr) {
					if ((pWindow = *itr) == NULL) break;

					if (CtInterface::checkWindowCategory(pWindow->getWindowID(), id)) {
						// 対象Windowを閉じ、再度対象Windowがないか確認を行う
						removeWindow(Screen, pWindow->getWindowID(), false);
						goto ConfirmAgain;
					}
				}
			}
			break;
		ConfirmAgain:	//goto
			continue;
		}
	}
	else {
		// カレント位置確認
		if (!(pWindow = pList->get(CtWindowList::Current))) {
			return false;
		}

		// 指定IDの探索
		if (!(pWindow = pList->get(id))) {
			return false;
		}

		if (!pList->removeWindow(id)) {
			return false;
		}

		destroyWindow(Sel, pWindow);
	}

	// 画面更新
	if (bUpdate) {
		pWindow = pList->get(CtWindowList::Current);
		if (pWindow) {
			pWindow->setInvalidate();
		}
	}

	return true;
}

bool CtWindowController::updateContents(CtScreenSel ScreenSel, CtWindowID id)
{
	bool bRet = false;
	CtWindowMain* pWindow = NULL;

	CtDebugPrint(CtDbg, "%s(%#x, %#x, %s)\n", __FUNCTION__, ScreenSel, id, CtWindowIDString::getString(id));


	for (int i = 0; i < m_CurrentAll.size(); i++) {
		if ((pWindow = m_CurrentAll[i]) == NULL)
			continue;

		if (pWindow->getWindowID() == id) {
			if (pWindow->updateContents() == true)
				bRet = true;
		}
	}

	return bRet;
}

CtWindowList* CtWindowController::getWindowList(int Screen) const
{
	if (Screen >= CT_SCREEN_NUM) return NULL;
	return m_WindowList[Screen];
}

CtWindowMain* CtWindowController::createWindow(CtScreenSel ScreenSel, CtWindowID id, CtWindowContents *pContents)
{
#if 1
	CtWindowMain *pWindow = NULL;

	pWindow = CtWindowFactory::create(ScreenSel, id, pContents);

#else
	CtWindowMain *pWindow = NULL;
	CtWindowList *pList = NULL;

	for (int Screen = 0; Screen < CT_SCREEN_NUM; Screen++) {
		if ((pList = getWindowList(toNoScreen(ScreenSel))) == NULL)
			continue;

		if ((pWindow = pList->get(id)) != NULL) {
			break;
		}
	}

	if (pWindow == NULL) {
		pWindow = CtWindowFactory::create(ScreenSel, id, pContents);
	}
#endif
	return pWindow;
}

void CtWindowController::destroyWindow(CtScreenSel ScreenSel, CtWindowMain* pWindow)
{
	if (pWindow == NULL)
		return;

	if (pWindow->destroy(ScreenSel)) {
		delete pWindow;
	}
}

CtWindowMain* CtWindowController::getCurrentWindow(int Screen) const
{
	CtWindowList *plist = getWindowList(Screen);

	if (!plist) return NULL;

	return plist->get(CtWindowList::Current);
}

CtWindowMain* CtWindowController::getRootWindow(int Screen) const
{
	CtWindowList *plist = getWindowList(Screen);

	if (!plist) return NULL;

	return plist->get(CtWindowList::Root);
}

CtWindowMain* CtWindowController::getWindow(int Screen, CtWindowID id) const
{
	CtWindowList *plist = getWindowList(Screen);

	if (!plist) return NULL;

	return plist->get(id);
}

CtWindowMain* CtWindowController::getDrawWindow(int Screen, CtWindowID id) const
{
	CtWindowList *pList = getWindowList(Screen);
	if (!pList) return NULL;

	const CtList::list<WindowList> &winlist = pList->getWidnowList();
	CtList::list<WindowList>::const_iterator Itr;
	WindowList List;
	CtWindowMain* pWindow;
	int pos;

	// リスト後方(前面のCtWindow)から対象Windowを探す
	Itr = winlist.end();
	for (pos = winlist.size() - 1; pos >= 0; pos--) {
		Itr--;
		List = *Itr;
		pWindow = *List.begin();
		CtWindowID WinID = pWindow->getWindowID();

		if (CtInterface::checkWindowCategory(WinID, id)) {
			return pWindow;
		}

		if (id == WinID) {
			return pWindow;
		}

		if ((pWindow->isViewing(Screen) == true) && (pWindow->isTransView())) {
			break;
		}
	}
	return NULL;
}

void CtWindowController::registerWindowFunc(CtWindowID id_win, CtFuncID id_func, CtWindowFunc func)
{
	m_FuncList[id_func].func = func;
	m_FuncList[id_func].id = static_cast<CtWindowID>(id_win);
}

void CtWindowController::unregisterWindowFunc(CtFuncID id_func)
{
	m_FuncList[id_func].func = NULL;
	m_FuncList[id_func].id = WindowNone;
}

bool CtWindowController::notifyWindowFunc(CtScreenSel ScreenSel, CtWindowID id_win, CtFuncID id_func, CtWindowContents* pContents)
{
	bool ret = false;
	if (id_func >= FuncID_MAX) return false;

	const CtWindowFuncTable *p = &m_FuncList[id_func];
	unsigned int WindowID = id_win;

	// FuncID_ALLの通知は常に行う
	if (m_FuncList[FuncID_ALL].func) {
		m_FuncList[FuncID_ALL].func(ScreenSel, id_win, id_func, pContents);
		ret = true;
	}

	if (p->func == NULL) return ret;

	// 登録済みCtWindowID値のMode/Title/Pageの各Bit部が0指定であれば
	// そのBit部を無視するためにWindowIDのBitを落とす
	if (((p->id >> 24) & 0xFF) == 0x00)	WindowID &= ~(0xFF000000);		//!< Mode部
	if (((p->id >> 16) & 0x00FF) == 0x00)	WindowID &= ~(0x00FF0000);		//!< Title部
	if (((p->id >> 0) & 0xFFFF) == 0x00)	WindowID &= ~(0x0000FFFF);			//!< Page部

	if (p->id == WindowID) {
		p->func(ScreenSel, id_win, id_func, pContents);
		ret = true;
	}

	return ret;
}

void CtWindowController::setNotifyFunc(CtNotifyFunc func)
{
	m_Notify = func;
}

void CtWindowController::setScreen(CtScreenSel ScreenSel)
{
	if (ScreenSel == m_ScreenOut) return;

	CtDebugPrint(CtDbg, "%s(Now:%x, Next:%x)\n", __FUNCTION__, m_ScreenOut, ScreenSel);

	for (int i = ScreenLCD; i < ScreenAll; i = i << 1) {
		if (!(m_ScreenOut & i) && (ScreenSel & i)) {
			// ScreenXXX OFF -> ON
			drawScreen(toNoScreen((CtScreenSel)i), 0);
		}
		else if ((m_ScreenOut & i) && !(ScreenSel & i)) {
			// ScreenXXX ON -> OFF
			clearScreen(toNoScreen((CtScreenSel)i), 0);
		}
	}

	m_ScreenOut = ScreenSel;
}

CtScreenSel CtWindowController::getScreen(void) const
{
	return m_ScreenOut;
}

/*
 カレントCtWindowの描画開始位置取得
*/
int CtWindowController::getDrawStart(int Screen)
{
	CtWindowList *pList = getWindowList(Screen);
	if (!pList) return 0;

	const CtList::list<WindowList> &winlist = pList->getWidnowList();
	CtList::list<WindowList>::const_iterator itr;
	WindowList List;

	// TransViewより前面のWindowのみ描画すればよいので
	// リスト後方(前面のCtWindow)からTransViewを探す
	itr = winlist.end();
	for (int i = winlist.size() - 1; i >= 0; i--) {
		itr--;
		List = *itr;
		CtWindowMain* pWindow = *List.begin();
		if ((pWindow->isAlive() == true) && (pWindow->isVisible() == true) && (pWindow->isTransView())) {
			return i;
		}
	}
	return 0;
}

// 全カレントウィンドウのInvalidate領域リスト取得
bool CtWindowController::getInvalidates(int Screen, CtWidget::RegionArray& invalidateArray)
{
	bool bRet = false;

	if (m_Current[Screen].empty() == true)
		return false;

	for (int i = m_VisiblePos[Screen]; i < m_Current[Screen].size(); i++) {
		if (m_Current[Screen][i] == NULL) continue;
		if (m_Current[Screen][i]->isAlive() != true) continue;
		if (m_Current[Screen][i]->getInvalidates(invalidateArray, Screen) == true)
			bRet = true;
	}

	return bRet;
}


bool CtWindowController::banFrameOperation(bool bBan)
{
	if (bBan == true) {
		if (m_bBanFrameOperation == true)
			return true;

		m_pDraw->getDrawing(true);
		m_bBanFrameOperation = true;
		m_pDraw->freeDrawing(true);

	}
	else {
		if (m_bBanFrameOperation != true)
			return true;

		m_bBanFrameOperation = false;
	}
	return true;
}
