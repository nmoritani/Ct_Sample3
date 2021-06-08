/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtEvent
 */
#ifndef __CtEvent_H__
#define __CtEvent_H__

#include "CtObject.h"
#include "Ct.h"

#include "CtMsg.h"
#include "CtMsgMainTask.h"
#include "AplParam.h"
#include "AplParamService.h"

class CtWidget;
class CtSynchro;

static const int Invalid = 0;

// DbgCmnd 制限 4Bit(0 ~ 15)
typedef enum EventGroup {
	ID_SYS_KEY = 1,		// SYS_CallBack Key
	ID_SYS_TOUCH,	// SYS_CallBack Touch
	ID_APL_PARAM,	// APL Param
	ID_TIMER,
	ID_FLASH,
	ID_BUTTON,
	ID_WIND,	// Window Windowition
	ID_REF_INFO,	// Refference Info
	ID_VAR_FUNC,	// ContentsCtrl
	ID_SHRT_CUT,						// ShortCut Event(Btn,Evnt,etc...)
	ID_APL_EVNT,						// APL Evnt(Rop, Ct_IF, etc...)
	ID_EVENT_GROUP_MAX = 16	// Invalid Value
}EventGroup;

class CtEvent : public CtMsg {
public:
	CtEvent();
	virtual ~CtEvent() {
	}

	// 送信
	void send() {
		CtMsgMainTask::sendMsg(*this);
	}
	virtual void operationCmd();
	// コマンド実行
	virtual bool exec() {
		return false;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////
class CtEventWindow : public CtEvent {
public:
	enum WinCmd {
		Change = 1,
		Popup,
		Swap,
		Return,
		Close,
		Remove,
		Redraw,
	};

	struct WindowArgs {
		CtScreenSel screen;
		CtWindowID id;
		CtWindowContents *pContents;
		CtWindowMain *pWindow;
		bool bDraw;
		CtColorFormat Format;
		WindowArgs() {
			memset(this, 0, sizeof(WindowArgs));
		}
		/*WindowArgs(const WindowArgs& args) {
			memcpy(this, &args, sizeof(args));
		}*/
	};

public:
	// Default
	CtEventWindow() :
		m_RequestCmdType(),
		m_WindowArgs() {
		createWindow();
	}

	// ArgSet
	CtEventWindow(WinCmd rqType, CtScreenSel screen, CtWindowID id, CtWindowContents *pContents, CtWindowMain *pWin, bool bDraw, CtColorFormat Format) {
		m_RequestCmdType = rqType;
		m_WindowArgs.screen = screen;
		m_WindowArgs.id = id;
		m_WindowArgs.pContents = pContents;
		m_WindowArgs.pWindow = pWin;
		m_WindowArgs.bDraw = bDraw;
		m_WindowArgs.Format = Format;
		createWindow();
	}
	CtEventWindow(WinCmd rqType, CtScreenSel screen, CtWindowID id, bool bDraw) {
		m_RequestCmdType = rqType;
		m_WindowArgs.screen = screen;
		m_WindowArgs.id = id;
		m_WindowArgs.pContents = NULL;
		m_WindowArgs.pWindow = NULL;
		m_WindowArgs.bDraw = bDraw;
		m_WindowArgs.Format = Format_Window;
		createWindow();
	}
	CtEventWindow(WinCmd rqType, CtWindowID id) {
		m_RequestCmdType = rqType;
		m_WindowArgs.screen = ScreenAll;
		m_WindowArgs.id = id;
		m_WindowArgs.pContents = NULL;
		m_WindowArgs.pWindow = NULL;
		m_WindowArgs.bDraw = true;
		m_WindowArgs.Format = Format_Window;
		createWindow();
	}
	CtEventWindow(WinCmd rqType, CtWindowID id, CtWindowContents *pContents) {
		m_RequestCmdType = rqType;
		m_WindowArgs.screen = ScreenAll;
		m_WindowArgs.id = id;
		m_WindowArgs.pContents = pContents;
		m_WindowArgs.pWindow = NULL;
		m_WindowArgs.bDraw = true;
		m_WindowArgs.Format = Format_Window;
		createWindow();
	}
	// Copy
	CtEventWindow(const CtEventWindow& Obj) :
		m_RequestCmdType(Obj.getEventType()),
		m_WindowArgs(Obj.m_WindowArgs) {
		createWindow();
	}
	// WidowMainのCreateWindow
	void createWindow();
	void setArgs(WinCmd rqType, const WindowArgs& Args) {
		m_RequestCmdType = rqType;
		m_WindowArgs = Args;
		createWindow();
	}

	void setArgs(const CtEventWindow& Obj) {
		this->m_RequestCmdType = Obj.getEventType();
		this->m_WindowArgs = Obj.getArgs();
		createWindow();
	}

	void setArgs(WinCmd rqType, CtScreenSel screen, CtWindowID id, CtWindowContents *pContents, CtWindowMain *pWin, bool bDraw, CtColorFormat Format) {
		m_RequestCmdType = rqType;
		m_WindowArgs.screen = screen;
		m_WindowArgs.id = id;
		m_WindowArgs.pContents = pContents;
		m_WindowArgs.pWindow = pWin;
		m_WindowArgs.bDraw = bDraw;
		m_WindowArgs.Format = Format;
		createWindow();
	}

	virtual ~CtEventWindow() {}
	WinCmd getEventType() const;
	WindowArgs getArgs() const;
	virtual bool exec();
private:
	WindowArgs m_WindowArgs;
	WinCmd m_RequestCmdType;
};

inline CtEventWindow::WinCmd CtEventWindow::getEventType() const {
	return m_RequestCmdType;
}

inline CtEventWindow::WindowArgs CtEventWindow::getArgs() const {
	return m_WindowArgs;
}
////////////////////////////////////////////////////////////////////////////////////////////////
class CtEventWinInfoAccess : public CtEvent {
public:
	enum WinInfoAccess {
		UpdateContents = 1,
		SetScreen,
		GetCurrentWindow,
		GetRootWindow,
		PermitDrawing,
		checkDrawWindow,
		OutLineDisp,
		PermitTransition,
		EventFilter,
	};

	union WinInfoArgs {
		struct WinInfoCntsArgs {
			CtScreenSel screen;
			CtWindowID id;
			CtWindowContents *pContents;
			CtWindowMain *pWindow;
			bool bDraw;
		}WinInfoCnts;

		struct WindowInfoArgs {
			CtScreenSel screen;
			CtSynchro    *pSynchro;
			CtWindowInfo *pWindowInfo;
			bool bFlg;
		}WindowInfoArgs;

		struct WindowDorwInfoArgs {
			CtScreenSel screen;
			CtWindowID id;
			CtSynchro    *pSynchro;
			CtWindowInfo *pWindowInfo;
		}WindowDorwInfoArgs;

		WinInfoArgs() {
			memset(this, 0, sizeof(WinInfoArgs));
		}

		/*WinInfoArgs(const WinInfoArgs& args) {
			memcpy(this, &args, sizeof(args));
		}*/
	};

public:
	// Default
	CtEventWinInfoAccess() :
		m_RequestCmdType((WinInfoAccess)Invalid),
		m_WinInfoAcsArgs() {
	}
	// ArgSet
	CtEventWinInfoAccess(WinInfoAccess rqType, CtScreenSel screen, CtWindowInfo * pInfo, CtSynchro * pSync)
	{
		m_RequestCmdType = rqType;
		m_WinInfoAcsArgs.WindowInfoArgs.screen = screen;
		m_WinInfoAcsArgs.WindowInfoArgs.pSynchro = pSync;
		m_WinInfoAcsArgs.WindowInfoArgs.pWindowInfo = pInfo;
	}

	CtEventWinInfoAccess(WinInfoAccess rqType, CtScreenSel screen, bool bPermit) {
		m_RequestCmdType = rqType;
		m_WinInfoAcsArgs.WindowInfoArgs.screen = screen;
		m_WinInfoAcsArgs.WindowInfoArgs.bFlg = bPermit;
	}

	CtEventWinInfoAccess(WinInfoAccess rqType, CtScreenSel screen, CtWindowID id,
		CtWindowContents *pContents, CtWindowMain *pWin, bool bDraw) {
		m_RequestCmdType = rqType;
		m_WinInfoAcsArgs.WinInfoCnts.screen = screen;
		m_WinInfoAcsArgs.WinInfoCnts.id = id;
		m_WinInfoAcsArgs.WinInfoCnts.pContents = pContents;
		m_WinInfoAcsArgs.WinInfoCnts.pWindow = pWin;
		m_WinInfoAcsArgs.WinInfoCnts.bDraw = bDraw;
	}
	
	CtEventWinInfoAccess(WinInfoAccess rqType, CtScreenSel screen, CtWindowID id, CtWindowInfo * pInfo, CtSynchro * pSync)
	{
		m_RequestCmdType = rqType;
		m_WinInfoAcsArgs.WindowDorwInfoArgs.screen = screen;
		m_WinInfoAcsArgs.WindowDorwInfoArgs.id = id;
		m_WinInfoAcsArgs.WindowDorwInfoArgs.pSynchro = pSync;
		m_WinInfoAcsArgs.WindowDorwInfoArgs.pWindowInfo = pInfo;
	}

	// Copy
	CtEventWinInfoAccess(const CtEventWinInfoAccess& Obj) :
		m_RequestCmdType(Obj.getEventType()),
		m_WinInfoAcsArgs(Obj.getArgs()) {
	}

	void setArgs(const CtEventWinInfoAccess& Obj) {
		this->m_RequestCmdType = Obj.getEventType();
		this->m_WinInfoAcsArgs = Obj.getArgs();
	}
	void setArgs(const WinInfoArgs& Args) {
		this->m_WinInfoAcsArgs = Args;
	}
	void setArgs(WinInfoAccess rqType, CtScreenSel screen, CtWindowInfo * pInfo, CtSynchro * pSync)
	{
		m_RequestCmdType = rqType;
		m_WinInfoAcsArgs.WindowInfoArgs.screen = screen;
		m_WinInfoAcsArgs.WindowInfoArgs.pSynchro = pSync;
		m_WinInfoAcsArgs.WindowInfoArgs.pWindowInfo = pInfo;
	}

	void setArgs(WinInfoAccess rqType, CtScreenSel screen, bool bPermit) {
		m_RequestCmdType = rqType;
		m_WinInfoAcsArgs.WindowInfoArgs.screen = screen;
		m_WinInfoAcsArgs.WindowInfoArgs.bFlg = bPermit;
	}

	void setArgs(WinInfoAccess rqType, CtScreenSel screen, CtWindowID id,
		CtWindowContents *pContents, CtWindowMain *pWin, bool bDraw) {
		m_RequestCmdType = rqType;
		m_WinInfoAcsArgs.WinInfoCnts.screen = screen;
		m_WinInfoAcsArgs.WinInfoCnts.id = id;
		m_WinInfoAcsArgs.WinInfoCnts.pContents = pContents;
		m_WinInfoAcsArgs.WinInfoCnts.pWindow = pWin;
		m_WinInfoAcsArgs.WinInfoCnts.bDraw = bDraw;
	}

	virtual ~CtEventWinInfoAccess() {}
	WinInfoAccess getEventType() const;
	WinInfoArgs getArgs() const;
	virtual bool exec();
private:
	WinInfoArgs m_WinInfoAcsArgs;
	WinInfoAccess m_RequestCmdType;
};
inline CtEventWinInfoAccess::WinInfoAccess CtEventWinInfoAccess::getEventType() const {
	return m_RequestCmdType;
}
inline CtEventWinInfoAccess::WinInfoArgs CtEventWinInfoAccess::getArgs() const {
	return m_WinInfoAcsArgs;
}

////////////////////////////////////////////////////////////////////////////////////////////////
class CtEventSys : public CtEvent
{
public:
	// Default
	CtEventSys() :
		m_Event(0) {
		memset(&m_Data, 0, sizeof(m_Data));
	}
	// SetArgs
	CtEventSys(unsigned long EventType, SYS_EVENT_DATA Data) :
		m_Event(EventType),
		m_Data(Data) {
	}
	// Copy
	CtEventSys(const CtEventSys& Obj) {
		this->m_Event = Obj.getEvent();
		this->m_Data = Obj.getSysData();
	}

	void setArgs(const CtEventSys& Obj) {
		this->m_Event = Obj.getEvent();
		this->m_Data = Obj.getSysData();
	}
	void setArgs(unsigned long EventType, SYS_EVENT_DATA Data) {
		this->m_Event = EventType;
		this->m_Data = Data;
	}

	virtual ~CtEventSys() {
	}

	virtual bool exec();

	SYS_EVENT_DATA getSysData() const;
	unsigned long getEvent() const;
private:
	SYS_EVENT_DATA m_Data;
	unsigned long m_Event;
};
inline SYS_EVENT_DATA CtEventSys::getSysData() const {
	return m_Data;
}
inline unsigned long CtEventSys::getEvent() const {
	return m_Event;
}
////////////////////////////////////////////////////////////////////////////////////////////////
/* ユーザー操作のうち、キーイベントを扱うクラス */
class CtEventKey : public CtEvent
{
public:
	/* キー動作 */
	typedef enum KeyAction {
		PressReleaseInvalid = Invalid,
		Press = 1,				/* キー押し */
		LongPress,				/* キー離し */
		RepeatPress,			/* キーリピート */
		Release,				/* キー離し */
		FastPress,				/* キー高速押し */
	} KeyAction;

	typedef enum KeyTimerLevel {
		Level_Invalid = Invalid,
		Level_Default = 1,
		Level1,
		Level2,
		Level3,
		Level4,
		Level5,
		Level6,
		Level_Max
	}KeyTimerLevel;
	/* イベント用キーコード */
	typedef enum KeyCode {
		KeyCode_Invalid = Invalid,
		KeyCode_Up = 1,			/* 上 */
		KeyCode_Down,			/* 下 */
		KeyCode_Left,			/* 左 */
		KeyCode_Right,			/* 右 */
		KeyCode_Enter,			/* 決定 */
		KeyCode_ManualFunction, /* マニュアルファンクションキー */
		KeyCode_MmrPlus,		/* マルチマニュアルリング +側 */
		KeyCode_MmrMinus,		/* マルチマニュアルリング -側 */
		KeyCode_User1,			/* USER1 */
		KeyCode_User2,			/* USER2 */
		KeyCode_User3,			/* USER3 */
		KeyCode_User4,			/* USER4 */
		KeyCode_User5,			/* USER5 */
		KeyCode_User6,			/* USER6 */
		KeyCode_User7,			/* USER7 */
		KeyCode_User8,			/* USER8 */
		KeyCode_User9,			/* USER9 */
		KeyCode_Menu,			/* MENU */
		KeyCode_Home,			/* HOME */
		KeyCode_Thumb,			/* THUMBNAIL */
		KeyCode_Exit,			/* EXIT */
		KeyCode_IrisFunc,		/* IRIS Dial Push */
		KeyCode_GripMenu,		/* (Grip) MENU */
		KeyCode_GripUser1,		/* (Grip) USER1 */
		KeyCode_GripUser2,		/* (Grip) USER2 */
		KeyCode_GripUser3,		/* (Grip) USER3 */
		KeyCode_GripUser4,		/* (Grip) USER4 */
		KeyCode_GripUser5,		/* (Grip) USER5 */
		KeyCode_GripUser6,		/* (Grip) USER6 */
		KeyCode_GripUser7,		/* (Grip) USER7 */
		KeyCode_GripUser8,		/* (Grip) USER8 */
		KeyCode_GripUser9,		/* (Grip) USER9 */
		KeyCode_Shift,			/* Shift */
		KeyCode_LockOn,			/* (Slide)Lock On */
		KeyCode_LockOff,		/* (Slide)Lock Off */
		KeyCode_Reset,			/* TC Set/Reset */
		KeyCode_AudioPlus,		/* Audio Plus */
		KeyCode_AudioMinus,		/* Audio Minus */
		KeyCode_DispCheck,		/* Disp Check */
		KeyCode_DialPressDown,	/* DialPressDown */
		KeyCode_DialPressUp,	/* DialPressUp */
		KeyCode_Max				/* Max */
	} KeyCode;

	/* キー送信元 */
	typedef enum KeySource {
		KeySource_Invalid = Invalid,	// Invalid
		KeySource_Body = 1,				// 本体
		KeySource_Remocon,				// 
		KeySource_Cec,					// 使用機種無し
		KeySource_Self,					// 用途不明
		KeySource_Controller,			// Rop
		KeySource_Grip,					// Grip
		KeySource_Lanc,					// Lancリモコン(3rdPartyLancリモコン)
		KeySource_Max,		// 有効範囲指定
		KeySource_Body2,	// ※DbgTsk用に生成(GUI内部ではKeySource_Bodyを使用する事)
	} KeySource;
	// Default
	CtEventKey() :
		m_KeyAction((KeyAction)Invalid),
		m_KeyCode((KeyCode)Invalid),
		m_KeySource((KeySource)Invalid),
		m_TimLv((KeyTimerLevel)Invalid) {
	}
	// ArgSet
	CtEventKey(KeyAction action, KeyCode code, KeySource source, KeyTimerLevel timLv = Level_Default) :
		m_KeyAction(action),
		m_KeyCode(code),
		m_KeySource(source),
		m_TimLv(timLv) {
	}
	CtEventKey(const CtEventKey& Obj) {
		this->m_KeyAction = Obj.getKeyAction();
		this->m_KeyCode = Obj.getKeyCode();
		this->m_KeySource = Obj.getKeySource();
		this->m_TimLv = Obj.getTimLv();
	}
	void setArgs(KeyAction action, KeyCode code, KeySource source, KeyTimerLevel timLv = Level_Default) {
		m_KeyAction = action;
		m_KeyCode = code;
		m_KeySource = source;
		m_TimLv = timLv;
	}
	void setArgs(const CtEventKey& Obj) {
		this->m_KeyAction = Obj.getKeyAction();
		this->m_KeyCode = Obj.getKeyCode();
		this->m_KeySource = Obj.getKeySource();
		this->m_TimLv = Obj.getTimLv();
	}

	KeyAction getKeyAction() const;
	KeyCode getKeyCode() const;
	KeySource getKeySource() const;
	KeyTimerLevel getTimLv() const;

	KeyTimerLevel m_TimLv;
	virtual bool exec();
	virtual ~CtEventKey() {}
private:
	KeyAction m_KeyAction;
	KeyCode m_KeyCode;
	KeySource m_KeySource;
};

inline CtEventKey::KeyAction CtEventKey::getKeyAction() const
{
	return m_KeyAction;
}

inline CtEventKey::KeyCode CtEventKey::getKeyCode() const
{
	return m_KeyCode;
}

inline CtEventKey::KeySource CtEventKey::getKeySource() const
{
	return m_KeySource;
}
inline CtEventKey::KeyTimerLevel CtEventKey::getTimLv() const
{
	return m_TimLv;
}
////////////////////////////////////////////////////////////////////////////////////////////////
/* ユーザ操作イベントのうち、タッチイベントを表すクラス */

class CtEventTouch : public CtEvent
{
public:
	typedef enum TouchAction {
		Press = 1,				/* タッチ */
		Move,					/* タッチドラッグ */
		Release,				/* タッチ離し */
		Slide					/* スライド */
	} TouchAction;

	typedef struct TouchPosition {
		short m_X;
		short m_Y;
	} TouchPosition;
	// Default
	CtEventTouch() :
		m_Action((TouchAction)Invalid) {
		memset(&m_Position, 0, sizeof(m_Position));
	}
	// ArgSet

	CtEventTouch(TouchAction touchAction, short x, short y) :
		m_Action(touchAction) {
		m_Position.m_X = x;
		m_Position.m_Y = y;
		/* SYS 通知座標系 → GUI 系通知座標系への変換 */
		convertCoordinate(m_Position);
	}
	// Copy
	CtEventTouch(const CtEventTouch& Obj) :
		m_Action(Obj.getAction()),
		m_Position(Obj.getPosition()) {
	}
	void setArgs(TouchAction touchAction, short x, short y) {
		m_Action = touchAction;
		m_Position.m_X = x;
		m_Position.m_Y = y;
		convertCoordinate(m_Position);
	}
	void setArgs(const CtEventTouch& Obj) {
		m_Action = Obj.getAction();
		m_Position = Obj.getPosition();
	}
	TouchAction getAction() const;
	TouchPosition getPosition() const;

	virtual ~CtEventTouch() {}
	virtual bool exec();
protected:
	typedef struct Coordinate {
		long m_W;
		long m_H;
	} Coordinate;
	void convertCoordinate(CtEventTouch::TouchPosition& pos);
private:
	TouchAction m_Action;		/* タッチ操作 */
	TouchPosition m_Position;	/* タッチ座標 */
};

/* タッチ操作を返す */
inline CtEventTouch::TouchAction CtEventTouch::getAction() const
{
	return m_Action;
}

/* タッチ座標を返す */
inline CtEventTouch::TouchPosition CtEventTouch::getPosition() const
{
	return m_Position;
}

/* SYS 通知の座標系を GUI 座標系に変換 */
inline void CtEventTouch::convertCoordinate(CtEventTouch::TouchPosition& pos)
{
#ifndef WIN32_GUI_SIM			/* シミュレーター環境では変換の必要なし */
	/*static*/ const CtEventTouch::Coordinate CoordinateSys = { 360, 240 };
	/*static*/ const CtEventTouch::Coordinate CoordinateGui = { 960, 640 };

	/* 小数点以下 3 桁の精度で計算 */
	pos.m_X = (short)(((pos.m_X * CoordinateGui.m_W * 1000) / CoordinateSys.m_W) / 1000);
	pos.m_Y = (short)(((pos.m_Y * CoordinateGui.m_H * 1000) / CoordinateSys.m_H) / 1000);
#endif	/* WIN32_GUI_SIM */
}

////////////////////////////////////////////////////////////////////////////////////////////////
/* ユーザ操作イベントのうち、タッチスライドイベントを表すクラス */
class CtEventTouchSlide : public CtEventTouch
{
public:
	/* スライド方向 */
	typedef enum SlideDirection {
		SlideUp = 1,
		SlideDown,
		SlideLeft,
		SlideRight
	} SlideDirection;
	// Default
	CtEventTouchSlide() {
		memset(&m_PreTouchPos, 0, sizeof(m_PreTouchPos));
		memset(&m_SlideStartPos, 0, sizeof(m_SlideStartPos));
		memset(&m_SlideSpeed, 0, sizeof(m_SlideSpeed));
		memset(&m_SlideDir, 0, sizeof(m_SlideDir));
	}
	// ArgSet
	CtEventTouchSlide(SYS_TPANEL& touchPanel) :
		CtEventTouch(CtEventTouch::Slide, touchPanel.X, touchPanel.Y),
		m_PreTouchPos(),
		m_SlideStartPos(),
		m_SlideSpeed(touchPanel.SlideSpeed),
		m_SlideDir() {

		/* 前回タッチ座標 */
		m_PreTouchPos.m_X = touchPanel.SlidePreX;
		m_PreTouchPos.m_Y = touchPanel.SlidePreY;
		convertCoordinate(m_PreTouchPos);

		/* スライド開始座標 */
		m_SlideStartPos.m_X = touchPanel.SlideStartX;
		m_SlideStartPos.m_Y = touchPanel.SlideStartY;
		convertCoordinate(m_SlideStartPos);

		/* スライド方向 */
		switch (touchPanel.SlideDir) {
		case SYS_TPANEL_SLIDE_UP:
			m_SlideDir = CtEventTouchSlide::SlideUp;
			break;
		case SYS_TPANEL_SLIDE_DOWN:
			m_SlideDir = CtEventTouchSlide::SlideDown;
			break;
		case SYS_TPANEL_SLIDE_LEFT:
			m_SlideDir = CtEventTouchSlide::SlideLeft;
			break;
		case SYS_TPANEL_SLIDE_RIGHT:
			m_SlideDir = CtEventTouchSlide::SlideRight;
			break;
		default:					/* パラメータエラー */
			break;
		}
	}
	//// Copy
	//CtEventTouchSlide(const CtEventTouchSlide& Obj) {
	//	this->m_PreTouchPos = Obj.getPreTouchPos();
	//	this->m_SlideStartPos = Obj.getSlideStartPos();
	//	this->m_SlideSpeed = Obj.getSlideSpeed();
	//	this->m_SlideDir = Obj.getSlideDirection();
	//}

	void setArgs(const CtEventTouchSlide& Obj) {
		this->m_PreTouchPos = Obj.getPreTouchPos();
		this->m_SlideStartPos = Obj.getSlideStartPos();
		this->m_SlideSpeed = Obj.getSlideSpeed();
		this->m_SlideDir = Obj.getSlideDirection();
	}

	void setArgs(SYS_TPANEL& touchPanel) {
		/* 前回タッチ座標 */
		m_PreTouchPos.m_X = touchPanel.SlidePreX;
		m_PreTouchPos.m_Y = touchPanel.SlidePreY;
		convertCoordinate(m_PreTouchPos);

		/* スライド開始座標 */
		m_SlideStartPos.m_X = touchPanel.SlideStartX;
		m_SlideStartPos.m_Y = touchPanel.SlideStartY;
		convertCoordinate(m_SlideStartPos);

		m_SlideSpeed = touchPanel.SlideSpeed;

		/* スライド方向 */
		switch (touchPanel.SlideDir) {
		case SYS_TPANEL_SLIDE_UP:
			m_SlideDir = CtEventTouchSlide::SlideUp;
			break;
		case SYS_TPANEL_SLIDE_DOWN:
			m_SlideDir = CtEventTouchSlide::SlideDown;
			break;
		case SYS_TPANEL_SLIDE_LEFT:
			m_SlideDir = CtEventTouchSlide::SlideLeft;
			break;
		case SYS_TPANEL_SLIDE_RIGHT:
			m_SlideDir = CtEventTouchSlide::SlideRight;
			break;
		default:					/* パラメータエラー */
			break;
		}
	}

	CtEventTouch::TouchPosition getPreTouchPos() const;
	CtEventTouch::TouchPosition getSlideStartPos() const;
	unsigned int getSlideSpeed() const;
	SlideDirection getSlideDirection() const;

	virtual ~CtEventTouchSlide() {
	}
	virtual bool exec();

private:
	CtEventTouch::TouchPosition m_PreTouchPos;   /* 前回通知のタッチ座標 */
	CtEventTouch::TouchPosition m_SlideStartPos; /* スライド開始時の座標 */
	unsigned int m_SlideSpeed; /* スライド速度 (8:フリック, 7～1:速～遅, 0: 停止) */
	SlideDirection m_SlideDir; /* スライド方向 */
};

inline CtEventTouch::TouchPosition CtEventTouchSlide::getPreTouchPos() const
{
	return m_PreTouchPos;
}

inline CtEventTouch::TouchPosition CtEventTouchSlide::getSlideStartPos() const
{
	return m_SlideStartPos;
}

inline unsigned int CtEventTouchSlide::getSlideSpeed() const
{
	return m_SlideSpeed;
}

inline CtEventTouchSlide::SlideDirection CtEventTouchSlide::getSlideDirection() const
{
	return m_SlideDir;
}

////////////////////////////////////////////////////////////////////////////////////////////////

class CtEventTimer : public CtEvent
{
public:
	// Defaultは対応しない
	// ArgSet
	CtEventTimer(int Uid, void* pInstance, unsigned long cycTim) :
		m_Uid(Uid), m_pInstance(pInstance), m_CycTim(cycTim) {
		setClassType(CtClassType_EventTimer);
	}
	// Copy
	CtEventTimer(const CtEventTimer& Obj) {
		this->m_Uid = Obj.getTimeUid();
		this->m_pInstance = Obj.getInstance();
		this->m_CycTim = Obj.getCycTim();
		setClassType(CtClassType_EventTimer);
	}
	virtual ~CtEventTimer() {}
	// GetMethod
	inline int getTimeUid() const;
	inline void* getInstance() const;
	inline unsigned long getCycTim() const;

	virtual bool exec();
private:
	int m_Uid;
	void* m_pInstance;
	unsigned long m_CycTim;
};

inline void* CtEventTimer::getInstance() const {
	return m_pInstance;
}

inline int CtEventTimer::getTimeUid() const
{
	return m_Uid;
}
inline unsigned long CtEventTimer::getCycTim() const {
	return m_CycTim;
}
////////////////////////////////////////////////////////////////////////////////////////////////
/* AplParamからの変化通知イベントを表すクラス */
class CtEventParam : public CtEvent
{
public:
	typedef enum AplParamType {
		Number = AplParamInitialType_Number,
		String = AplParamInitialType_String,
		IP = AplParamInitialType_Ip,
	}AplParamInitType;
	// Default
	CtEventParam() {
		m_ParamId = AplParamIdMax;
		m_ParamVal = 0;
		setClassType(CtClassType_EventParam);
	}
	// ArgSet
	CtEventParam(int ParamId, int ParamVal) :
		m_ParamId(ParamId),
		m_ParamVal(ParamVal){
		setClassType(CtClassType_EventParam);
	}
	// Copy
	CtEventParam(CtEventParam& Event) :
		m_ParamId(Event.m_ParamId),
		m_ParamVal(Event.m_ParamVal){
		setClassType(CtClassType_EventParam);
	}
	void setArgs(int ParamId, int ParamVal) {
		m_ParamId = ParamId;
		m_ParamVal = ParamVal;
	}
	AplParamEepromId getParamId() const;
	int getParamVal() const;

	virtual bool exec();

	virtual ~CtEventParam() {
	}

private:
	int	m_ParamId;
	int	m_ParamVal;
};

inline AplParamEepromId CtEventParam::getParamId() const
{
	return (AplParamEepromId)m_ParamId;
}

inline int CtEventParam::getParamVal() const
{
	return m_ParamVal;
}

////////////////////////////////////////////////////////////////////////////////////////////////

class CtEventFlash : public CtEvent
{
public:
	enum Frequency {
		Freq_Invalid = Invalid,
		Freq_025Hz = 1,
		Freq_05Hz,
		Freq_1Hz,
		Freq_2Hz,
	};

	CtEventFlash(Frequency Freq, bool bShow) :
		m_Frequency(Freq),
		m_bShow(bShow) {
	}
	Frequency getFrequency() const;
	bool isShow() const;

	virtual ~CtEventFlash() {
	}

	virtual bool exec();
private:
	Frequency	m_Frequency;
	bool		m_bShow;
};

inline CtEventFlash::Frequency CtEventFlash::getFrequency() const
{
	return m_Frequency;
}

inline bool CtEventFlash::isShow() const
{
	return m_bShow;
}

////////////////////////////////////////////////////////////////////////////////////////////////
class CtEventButton : public CtEvent
{
public:
	enum PressType {
		PressInvalid = Invalid,
		ShortPress,
		LongPress,
		RepeatPress,
		Release,
	};

	// 状態変化対象一覧
	enum ChangeState {
		Stability = Invalid,
		Valid = 0x01,
		Visible = 0x02,
		Focus = 0x04,
		Select = 0x08,
		AllChange = (Valid | Visible | Focus)
	};
	typedef enum ButtonTimerLevel {
		Level_Invalid = Invalid,
		Level_Default = 1,
		Level1,
		Level2,
		Level3,
		Level4,
		Level5,
		Level6,
		Level_Max
	}ButtonTimerLevel;

	// Default
	CtEventButton() :
		m_WidgetID(0),
		m_pWidget(NULL),
		m_pWinMain(NULL),
		m_PressType(PressInvalid),
		m_ChangeState(Stability),
		m_TimLv(Level_Invalid) {
	}
	// ArgSet
	CtEventButton(unsigned long WidgetID, CtWidget* pWidget, CtWindowMain* pWinMain, PressType PressType, ButtonTimerLevel TimLv = Level_Default) :
		m_WidgetID(WidgetID),
		m_pWidget(pWidget),
		m_pWinMain(pWinMain),
		m_PressType(PressType),
		m_ChangeState(Stability),
		m_TimLv(TimLv) {
	}
	// ArgSet
	CtEventButton(unsigned long WidgetID, CtWidget* pWidget, CtWindowMain* pWinMain, ChangeState state, ButtonTimerLevel TimLv = Level_Default) :
		m_WidgetID(WidgetID),
		m_pWidget(pWidget),
		m_pWinMain(pWinMain),
		m_PressType(PressInvalid),
		m_ChangeState(state) ,
		m_TimLv(TimLv){
	}
	// Copy
	CtEventButton(const CtEventButton& Obj) :
		m_WidgetID(Obj.getWidgetID()),
		m_pWidget(Obj.getWidget()),
		m_pWinMain(Obj.getWinMain()),
		m_PressType(Obj.getPressType()),
		m_ChangeState(Obj.getChangeState()),
		m_TimLv(Obj.getTimLv()){
	}

	void setArgs(unsigned long WidgetID, CtWidget* pWidget, CtWindowMain* pWinMain, PressType PressType, ButtonTimerLevel TimLv = Level_Default) {
		m_WidgetID = WidgetID;
		m_pWidget = pWidget;
		m_pWinMain = pWinMain;
		m_PressType = PressType;
		m_ChangeState = Stability;
		m_TimLv = TimLv;
	}

	void setArgs(unsigned long WidgetID, CtWidget* pWidget, CtWindowMain* pWinMain, ChangeState state, ButtonTimerLevel TimLv = Level_Default) {
		m_WidgetID = WidgetID;
		m_pWidget = pWidget;
		m_pWinMain = pWinMain;
		m_PressType = PressInvalid;
		m_ChangeState = state;
		m_TimLv = TimLv;
	}

	void setArgs(const CtEventButton& Obj) {
		m_WidgetID = Obj.getWidgetID();
		m_pWidget = Obj.getWidget();
		m_pWinMain = Obj.getWinMain();
		m_PressType = Obj.getPressType();
		m_ChangeState = Obj.getChangeState();
		m_TimLv = Obj.getTimLv();
	}

	unsigned long getWidgetID() const;
	CtWidget *getWidget() const;
	CtWindowMain* getWinMain() const;
	PressType getPressType() const;
	ChangeState getChangeState() const;
	bool isChangeState() const;
	ButtonTimerLevel getTimLv() const;

	virtual ~CtEventButton() {}
	virtual bool exec();
private:
	unsigned long		m_WidgetID;
	CtWidget*			m_pWidget;
	CtWindowMain*		m_pWinMain;
	PressType			m_PressType;
	ChangeState			m_ChangeState;
	ButtonTimerLevel	m_TimLv;
};

inline unsigned long CtEventButton::getWidgetID() const
{
	return m_WidgetID;
}

inline CtWidget* CtEventButton::getWidget() const
{
	return m_pWidget;
}

inline CtWindowMain* CtEventButton::getWinMain() const
{
	return m_pWinMain;
}

inline CtEventButton::PressType CtEventButton::getPressType() const
{
	return m_PressType;
}

inline bool CtEventButton::isChangeState() const {
	if (m_ChangeState == Stability) {
		return false;
	}
	return true;
}

inline CtEventButton::ChangeState CtEventButton::getChangeState() const {
	return m_ChangeState;
}
inline CtEventButton::ButtonTimerLevel CtEventButton::getTimLv()  const {
	return m_TimLv;
}
////////////////////////////////////////////////////////////////////////////////////////////////
class CtEventWidget : public CtEvent
{
public:
	enum Request {
		None,
		StartWindow,
		RestartWindow,
		TermWindow,
		ToBackSide,
		ToFrontSide,
		
		StartWidget,
		RestartWidget,
		TermWidget,

		RequestMax
	};

	// Default
	CtEventWidget() :
		m_WidgetID(0),
		m_pWidget(NULL),
		m_Request(None) {
		setClassType(CtClassType_EventWidget);
	}
	// ArgSet
	CtEventWidget(unsigned long WidgetID, CtWidget* pWidget, Request Req, CtWindowMain* pWinMain = NULL) :
		m_WidgetID(WidgetID),
		m_pWidget(pWidget),
		m_pWinMain(pWinMain),
		m_Request(Req) {
		setClassType(CtClassType_EventWidget);
	}
	// Copy
	CtEventWidget(const CtEventWidget& Obj) :
		m_WidgetID(Obj.getWidgetID()),
		m_pWidget(Obj.getWidget()),
		m_pWinMain(Obj.getWinMain()),
		m_Request(Obj.getRequest()) {
		setClassType(CtClassType_EventWidget);
	}

	void setArgs(unsigned long WidgetID, CtWidget* pWidget, Request Req, CtWindowMain* pWinMain = NULL) {
		m_WidgetID = WidgetID;
		m_pWidget = pWidget;
		m_Request = Req;
		m_pWinMain = pWinMain;
	}

	void setArgs(const CtEventWidget& Obj) {
		m_WidgetID = Obj.getWidgetID();
		m_pWidget = Obj.getWidget();
		m_Request = Obj.getRequest();
		m_pWinMain = Obj.getWinMain();
	}

	unsigned long getWidgetID() const;
	CtWidget *getWidget() const;
	CtWindowMain *getWinMain() const;
	Request getRequest() const;

	virtual ~CtEventWidget() {}
	virtual bool exec();
private:
	unsigned long	  m_WidgetID;
	CtWidget*		  m_pWidget;
	CtWindowMain*	  m_pWinMain;
	Request			  m_Request;
};

inline unsigned long CtEventWidget::getWidgetID() const
{
	return m_WidgetID;
}

inline CtWindowMain* CtEventWidget::getWinMain() const {
	return m_pWinMain;
}

inline CtWidget* CtEventWidget::getWidget() const
{
	return m_pWidget;
}

inline CtEventWidget::Request CtEventWidget::getRequest() const
{
	return m_Request;
}


////////////////////////////////////////////////////////////////////////////////////////////////
class CtEventFunc : public CtEvent
{
public:
	struct FuncArgs {
		CtScreenSel screen;
		CtWindowID id;
		CtFuncID funcId;
		CtWindowContents *pContents;
		FuncArgs() {
			memset(this, 0, sizeof(FuncArgs));
		}
	};

	// Default
	CtEventFunc() {
		m_FuncArgs.screen = ScreenAll;
		m_FuncArgs.id = WindowNone;
		m_FuncArgs.funcId = FuncID_ALL;
		m_FuncArgs.pContents = NULL;
	}

	// ArgSet
	CtEventFunc(CtScreenSel screen, CtWindowID id, CtFuncID funcId, CtWindowContents* pContents) {
		m_FuncArgs.screen = screen;
		m_FuncArgs.id = id;
		m_FuncArgs.funcId = funcId;
		m_FuncArgs.pContents = pContents;
	}

	// Copy
	CtEventFunc(CtEventFunc& Obj) {
		m_FuncArgs = Obj.m_FuncArgs;
	}

	virtual ~CtEventFunc() {}
	void setArgs(CtScreenSel screen, CtWindowID id, CtFuncID funcId, CtWindowContents* pContents) {
		m_FuncArgs.screen = screen;
		m_FuncArgs.id = id;
		m_FuncArgs.funcId = funcId;
		m_FuncArgs.pContents = pContents;
	}

	void setArgs(const CtEventFunc& Obj) {
		this->m_FuncArgs = Obj.getArgs();
	}
	void setArgs(const FuncArgs& funcArgs) {
		this->m_FuncArgs = funcArgs;
	}
	FuncArgs getArgs() const;
	virtual bool exec();
private:
	FuncArgs m_FuncArgs;
};

inline CtEventFunc::FuncArgs CtEventFunc::getArgs() const {
	return m_FuncArgs;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
class CtEventDrawResult : public CtEvent
{
public:
	struct DrawArgs {
		CtScreenSel Screen;
		CtWindowID WindowId;
		CtWindowMain* pWinMain;
		DrawArgs() {
			memset(this, 0, sizeof(DrawArgs));
		}
	};

	CtEventDrawResult() :
		m_DrawArgs() {
		setClassType(CtClassType_EventDrawResult);
	}

	CtEventDrawResult(CtScreenSel screen, CtWindowID id, CtWindowMain* pWinMain) {
		m_DrawArgs.Screen = screen;
		m_DrawArgs.WindowId = id;
		m_DrawArgs.pWinMain = pWinMain;
		setClassType(CtClassType_EventDrawResult);
	}

	CtEventDrawResult(const DrawArgs& Args) :
		m_DrawArgs(Args) {
		setClassType(CtClassType_EventDrawResult);
	}

	CtEventDrawResult(const CtEventDrawResult& Obj) :
		m_DrawArgs(Obj.getArgs()) {
		setClassType(CtClassType_EventDrawResult);
	}
	void setArgs(CtScreenSel screen, CtWindowID id, CtWindowMain* pWinMain) {
		m_DrawArgs.Screen = screen;
		m_DrawArgs.WindowId = id;
		m_DrawArgs.pWinMain = pWinMain;
	}
	void setArgs(const CtEventDrawResult& Obj) {
		this->m_DrawArgs = Obj.getArgs();
	}
	void setArgs(const DrawArgs& DrawArgs) {
		this->m_DrawArgs = DrawArgs;
	}

	virtual ~CtEventDrawResult() {}
	DrawArgs getArgs() const;
	virtual bool exec();
private:
	DrawArgs m_DrawArgs;
};

inline CtEventDrawResult::DrawArgs CtEventDrawResult::getArgs() const {
	return m_DrawArgs;
}

class CtEventRequest : public CtEvent
{
public:
	enum RequestType {
		None,
		ThumbElement,
		ThumbImage,
	};

	// Default
	CtEventRequest() :
		m_WidgetID(0),
		m_pWidget(NULL),
		m_RequestType(None),
		m_RequestId(0) {
	}
	// ArgSet
	CtEventRequest(unsigned long WidgetID, CtWidget* pWidget, RequestType Type, int Id) :
		m_WidgetID(WidgetID),
		m_pWidget(pWidget),
		m_RequestType(Type),
		m_RequestId(Id) {
	}
	// ArgSet
	// Copy
	CtEventRequest(const CtEventRequest& Obj) :
		m_WidgetID(Obj.getWidgetID()),
		m_pWidget(Obj.getWidget()),
		m_RequestType(Obj.getRequestType()),
		m_RequestId(Obj.getRequestId()) {
	}
	void setArgs(unsigned long WidgetID, CtWidget* pWidget, RequestType Type, int Id) {
		m_WidgetID = WidgetID;
		m_pWidget = pWidget;
		m_RequestType = Type;
		m_RequestId = Id;
	}
	void setArgs(const CtEventRequest& Obj) {
		m_WidgetID = Obj.getWidgetID();
		m_pWidget = Obj.getWidget();
		m_RequestType = Obj.getRequestType();
		m_RequestId = Obj.getRequestId();
	}

	unsigned long getWidgetID() const;
	CtWidget *getWidget() const;
	RequestType getRequestType() const;
	int getRequestId() const;

	virtual ~CtEventRequest() {}
	virtual bool exec();
private:
	unsigned long	m_WidgetID;
	CtWidget*		m_pWidget;
	RequestType 	m_RequestType;
	int				m_RequestId;
};

inline unsigned long CtEventRequest::getWidgetID() const
{
	return m_WidgetID;
}

inline CtWidget* CtEventRequest::getWidget() const
{
	return m_pWidget;
}

inline CtEventRequest::RequestType CtEventRequest::getRequestType() const
{
	return m_RequestType;
}

inline int CtEventRequest::getRequestId() const
{
	return m_RequestId;
}

#endif	/* __CtEvent_H__ */
