/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindowController
 */

#ifndef __CtWindowController_H__
#define __CtWindowController_H__

#include "CtClass.h"
#include "Ct.h"
#include "CtWidget.h"
#include "CtDraw.h"
#include "CtTimer.h"
#include "CtWindowDecorate.h"

class CtWindowController : public CtObject
{
public:
	virtual ~CtWindowController();
	static CtWindowController* getInstance();
	
	// Window管理
	typedef CtList::list<CtWindowMain*> WindowList;
	CtWindowMain* createWindow(CtScreenSel ScreenSel, CtWindowID id, CtWindowContents *pContents);
	
	CtWindowMain* getCurrentWindow(int Screen) const;
	CtWindowMain* getRootWindow(int Screen) const;
	CtWindowMain* getWindow(int Screen, CtWindowID id) const;
	CtWindowMain* getDrawWindow(int Screen, CtWindowID id) const;
	
	// コールバック管理
	void registerWindowFunc(CtWindowID id_win, CtFuncID id_func, CtWindowFunc func);
	void unregisterWindowFunc(CtFuncID id_func);
	bool notifyWindowFunc(CtScreenSel ScreenSel, CtWindowID id_win, CtFuncID id_func, CtWindowContents* pContents);

	// その他API向け
	void setNotifyFunc(CtNotifyFunc func);
	void setScreen(CtScreenSel ScreenSel);
	CtScreenSel getScreen(void) const;
	CtScreenInfo getScreenInfo(CtScreenSel ScreenSel) const;
		
	bool handleFrameSync(unsigned long FrameCount);
	
private:
	static CtWindowController* m_pInstance;
	static const int m_PopupWindowLimit		= 20;				//!< PopupWindow最大数
	static const int m_ChangeWindowLimit	= 30;				//!< ChangeWindow最大数
	CtWindowList *m_WindowList[CT_SCREEN_NUM];					//!< 各SCREEN用ウィンドウリスト
	CtScreenSel m_ScreenOut;									//!< 各スクリーンの有効/無効情報
	CtDraw *m_pDraw;											//!< Drawクラスインスタンス
	CtTimer *m_pTimer;											//!< Timerクラスインスタンス
	CtNotifyFunc m_Notify;										//!< 上位ブロックへのコールバック関数
	struct CtWindowFuncTable {
		CtWindowID id;
		CtWindowFunc func;
	} m_FuncList[FuncID_MAX];									//!< Functionテーブル
	
	CtObserverParamService *m_pParamIf;					//!< パラメータサービスインスタンス

	CtWidget::RegionArray	m_Invalidates;
	CtWidget::RegionArray	m_InvalidatesFast;
	
	typedef CtVector::Vector<CtWindowMain*> WindowArray;
	WindowArray				m_CurrentAll;
	WindowArray				m_Current[CT_SCREEN_NUM];
	int						m_VisiblePos[CT_SCREEN_NUM];

	bool					m_bBanFrameOperation;
	
	// コンストラクタ
	CtWindowController();

	// Window管理
	CtWindowList* getWindowList(int Screen) const;
	void destroyWindow(CtScreenSel ScreenSel, CtWindowMain* pWindow);

	// 画面遷移
	bool changeWindow(int Screen, CtWindowID id, CtWindowContents* pContents, CtWindowMain* pWindow = NULL, bool bUpdate = true);
	bool popupWindow(int Screen, CtWindowID id, CtWindowContents* pContents, CtWindowMain* pWindow = NULL, bool bUpdate = true);
	bool swapWindow(int Screen, CtWindowID id, CtWindowContents* contents, CtWindowMain* pWindow = NULL, bool bUpdate = true);
	bool returnWindow(int Screen, CtWindowID id = WindowNone, bool bUpdate = true);
	bool closeWindow(int Screen, CtWindowID id = WindowNone, bool bUpdate = true);
	bool removeWindow(int Screen, CtWindowID id, bool bUpdate = true);

	// コンテンツ管理
	bool updateContents(CtScreenSel ScreenSel, CtWindowID id);

	// 画面描画
	bool readyWindow(CtWindowMain* pWindow);
	bool getInvalidates(int Screen, CtWidget::RegionArray& invalidateArray);
	bool drawScreen(int Screen, int delay);
	bool clearScreen(int Screen, int delay);
	bool drawScreenFast(int Screen);
	
	int getDrawStart(int Screen);
	bool banFrameOperation(bool bBan);
	//int	(CtScreenSel ScreenSelBit);
public:
	// イベント制御
	void putEvent(CtEvent& Event);
	bool KeyEvent(const CtEventKey& Key);
	bool WindowEvent(const CtEventWindow& Event);
	bool WinInfoEvent(const CtEventWinInfoAccess& Event);
	bool TouchEvent(const CtEventTouch& Touch);
	bool TimerEvent(const CtEventTimer& Timer);
	bool ParamEvent(const CtEventParam& Param);
	bool FlashEvent(const CtEventFlash& Flash);
	bool ButtonEvent(const CtEventButton& Button);
	bool WidgetEvent(const CtEventWidget& Widget);
	bool FuncEvent(const CtEventFunc& Event);
	bool DrawResultEvent(const CtEventDrawResult& Event);
	bool RequestEvent(const CtEventRequest& Request);
};

#endif

