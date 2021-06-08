/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:			CtInterface
*/

#ifndef __CtInterface_H__
#define __CtInterface_H__

#include "Ct.h"
#include "CtClass.h"
#include "CtEvent.h"
#include "CtObject.h"
#include "CtWindowContents.h"

class CtInterface : public CtObject
{
public:
	virtual ~CtInterface();
	static CtInterface* getInstance();

	/// ウィンドウ操作
	void changeWindow(CtScreenSel screen, CtWindowID id, CtWindowContents* contents = NULL, bool bDraw = true, CtColorFormat Format = Format_Window) const;
	void popupWindow(CtScreenSel screen, CtWindowID id, CtWindowContents* contents = NULL, bool bDraw = true) const;
	void returnWindow(CtScreenSel screen, CtWindowID id = WindowNone, bool bDraw = true) const;
	void closeWindow(CtScreenSel screen, CtWindowID id = WindowNone, bool bDraw = true) const;
	void swapWindow(CtScreenSel screen, CtWindowID id, CtWindowContents* contents = NULL, bool bDraw = true) const;
	void removeWindow(CtScreenSel screen, CtWindowID id, bool bDraw = true) const;

	// ウィンドウ情報取得
	CtWindowID getCurrentWindowID(CtScreenSel screen) const;
	CtWindowID getRootWindowID(CtScreenSel screen) const;
	CtWindowInfo getWindowInfo(CtScreenSel screen, CtWindowID id) const;
	CtWindowID checkDrawWindowID(CtScreenSel screen, CtWindowID id) const;
	static bool checkWindowCategory(CtWindowID WindowID);
	static bool checkWindowCategory(CtWindowID WindowID, CtWindowID CategoryID);

	// ウィンドウ情報操作
	void setEventFilter(CtWindowID id, CtEventFilter filter) const;
	CtEventFilter getEventFilter(CtWindowID id);
	void setWindowContents(CtScreenSel screen, CtWindowID id, CtWindowContents *contents) const;
	void registerWindowFunc(CtWindowID id_win, CtFuncID id_func, CtWindowFunc func) const;
	void registerWindowFunc(CtWindowFunc func) const;
	void unregisterWindowFunc(CtFuncID id_func) const;
	
	// スクリーン操作
	void setNotifyFunc(CtNotifyFunc func) const;
	void setScreen(CtScreenSel screen) const;
	CtScreenSel getScreen(void) const;
	CtScreenInfo getScreenInfo(CtScreenSel screen) const;
	void permitTransition(bool isAutoTrans) const;
	void permitDrawing(CtScreenSel screen, bool isDrawing) const;

	// キーイベント操作
	void putRopEvent(CtEventKey::KeyCode Key, CtEventKey::KeyAction Action);
		
	// デバッグ用
	void outputWindowOutline(CtScreenSel screen, CtWindowID id) const;

private:
	CtInterface();
	bool isCtTask() const;

	static CtInterface* m_pInstance;
	CtWindowController* m_pWc;
};


#endif
