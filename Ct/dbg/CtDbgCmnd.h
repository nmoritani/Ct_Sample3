#ifndef __CtDbgDmnd_H__
#define __CtDbgDmnd_H__

#include "Ct.h"
#include "CtEvent.h"

namespace  CtDbgCmndDomain {
	
	static const char ID_INVALID = 0;

	//static const int CMD_64BIT = 8;
	//static const int CMD_32BIT = 4;

	//static const int scrn32Bit = 28;
	//static const int cmndGrp32Bit = 24;
	//static const int cmndId32Bit = 16;

	//static const int scrn64Bit = 60;
	//static const int cmndGrp64Bit = 56;
	//static const int cmndId64Bit = 48;

	//static const int MSB_4U_MAX = 16;		// 無効値(0～15まで有効)
	//static const int MSB_8U_MAX = 256;		// 無効値(0～255まで有効)
	//static const int MSB_16U_MAX = 65536;	// 無効値(0～65535まで有効)

	//★★★★★★★★CmndGrp ★★★★★★★★
	static const int SCREEN_ALL = ScreenAll;

	typedef enum _DBG_CMND_SCRN_SEL {
		ID_NONE = ScreenNone,
		ID_LCD = ScreenLCD,
		ID_LOUT = ScreenLOUT,
		ID_SCRN_ALL = ScreenAll
	}DbgCmndScrnSel;

	//★★★★★★★★CmndGrp ★★★★★★★★


	//★★★★★★★★CmndId ★★★★★★★★
	typedef enum _DBG_CMND_WIN_TRANS_ID {
		ID_CHANGE = CtEventWindow::Change,
		ID_RETURN = CtEventWindow::Return,
		ID_POPUP = CtEventWindow::Popup,
		ID_CLOSE = CtEventWindow::Close,
		ID_SWAP = CtEventWindow::Swap,
		ID_REMOVE = CtEventWindow::Remove,
		ID_WIN_TRANS_MAX
	}DbgCmndWinTransId;

	typedef enum _DBG_CMND_REF_INFO_ID {
		ID_ROOT = CtEventWinInfoAccess::GetRootWindow,
		ID_CRNT = CtEventWinInfoAccess::GetCurrentWindow,
		ID_OUTLINE = CtEventWinInfoAccess::OutLineDisp,
		ID_CLASSINFO = ID_OUTLINE+1,
		ID_MEMINFO,
		ID_REF_INFO_MAX
	}DbgCmndRefInfoId;

	typedef enum _DBG_CMND_VAR_FUNC_ID {
		ID_VAR_FUNC_1 = 1,
		ID_VAR_FUNC_2,
		ID_VAR_FUNC_3,
		ID_VAR_FUNC_4,
		ID_VAR_FUNC_5,
		ID_VAR_FUNC_6,
		ID_VAR_FUNC_7,
		ID_VAR_FUNC_8,
		ID_VAR_FUNC_MAX
	}DbgCmndVarFuncId;

	typedef enum _DBG_CMND_SHRT_CUT_ID {
		ID_SHRT_HOME = 1,
		ID_SHRT_MENU,
		ID_SHRT_VIEW,
		ID_SHRT_THUM,
		ID_SHRT_INFO,
		ID_SHRT_PLAY,
		ID_SHRT_CLIP,
		ID_SHRT_CUT_MAX
	}DbgCmndShrtCutId;

	//////////////////KEY CMD ID//////////////////
	typedef enum _DBG_CMND_KEY_SRC_ID {
		ID_DECK = CtEventKey::KeySource_Body,
		ID_REMOCON = CtEventKey::KeySource_Remocon,
		ID_CEC = CtEventKey::KeySource_Cec,
		ID_SELF = CtEventKey::KeySource_Self,
		ID_Controller = CtEventKey::KeySource_Controller,
		ID_GRIP = CtEventKey::KeySource_Grip,
		ID_Lanc = CtEventKey::KeySource_Lanc, // K519でGripと分離(Grip操作同等)
		ID_DECK2 = CtEventKey::KeySource_Body2,
		ID_SRC_MAX 
	}DbgCmndKeySrcId;

	typedef enum _DBG_CMND_KEY_ACT_ID {
		ID_KEY_PRS = CtEventKey::Press,
		ID_KEY_RLS = CtEventKey::Release,
		ID_KEY_LNG_PRS = CtEventKey::LongPress,
		ID_KEY_RPT_PRS = CtEventKey::RepeatPress,
		ID_KEY_FAST_PRS = CtEventKey::FastPress,
		ID_KEY_ACT_MAX
	}DbgCmndKeyActId;
	///////////////////////////////////////////////

	typedef enum _DBG_CMND_TCH_ID {
		ID_TCH_PRS = CtEventTouch::Press,
		ID_TCH_RLS = CtEventTouch::Release,
		ID_TCH_MV = CtEventTouch::Move,
		ID_TCH_SLIDE = CtEventTouch::Slide,
		ID_TCH_MAX 
	}DbgCmndTchId;

	typedef enum _DBG_CMND_APL_PARAM_ID {
		ID_PARAM_NUM = CtEventParam::Number,
		ID_PARAM_STRING = CtEventParam::String,
		ID_PARAM_IP = CtEventParam::IP,
		ID_PARAM_MAX 
	}DbgCmndAplParamId;

	typedef enum _DBG_CMND_APL_EVNT_ID {
		ID_PERM_DRAW = CtEventWinInfoAccess::PermitDrawing,
		ID_PERM_TRNS = CtEventWinInfoAccess::PermitTransition,
		ID_EVNT_FILT = CtEventWinInfoAccess::EventFilter,
		ID_UP_CNTS = CtEventWinInfoAccess::UpdateContents,
		ID_CHK_DRAW_Win = CtEventWinInfoAccess::checkDrawWindow,
		ID_APL_EVNT_MAX 
	}DbgCmndAplEvntId;

	//★★★★★★★★Data Bit★★★★★★★★

	typedef enum _DBG_CMND_KEY_CODE_ID {
		ID_KEY_UP = CtEventKey::KeyCode_Up,
		ID_KEY_DOWN = CtEventKey::KeyCode_Down,
		ID_KEY_LEFT = CtEventKey::KeyCode_Left,
		ID_KEY_RIGHT = CtEventKey::KeyCode_Right,
		ID_KEY_ENTER = CtEventKey::KeyCode_Enter,
		ID_KEY_DIAL_UP = CtEventKey::KeyCode_MmrPlus,
		ID_KEY_DIAL_DOWN = CtEventKey::KeyCode_MmrMinus,
		ID_KEY_DIAL_FUNC = CtEventKey::KeyCode_ManualFunction,
		ID_KEY_EXIT = CtEventKey::KeyCode_Exit,
		ID_KEY_MENU = CtEventKey::KeyCode_Menu,
		ID_KEY_HOME = CtEventKey::KeyCode_Home,
		ID_KEY_MODE = CtEventKey::KeyCode_Thumb,
		ID_KEY_SHIFT = CtEventKey::KeyCode_Shift,
		ID_KEY_LOCK_ON = CtEventKey::KeyCode_LockOn,
		ID_KEY_LOCK_OFF = CtEventKey::KeyCode_LockOff,
		ID_KEY_USER1 = CtEventKey::KeyCode_User1,
		ID_KEY_USER2 = CtEventKey::KeyCode_User2,
		ID_KEY_USER3 = CtEventKey::KeyCode_User3,
		ID_KEY_USER4 = CtEventKey::KeyCode_User4,
		ID_KEY_USER5 = CtEventKey::KeyCode_User5,
		ID_KEY_USER6 = CtEventKey::KeyCode_User6,
		ID_KEY_USER7 = CtEventKey::KeyCode_User7,
		ID_KEY_USER8 = CtEventKey::KeyCode_User8,
		ID_KEY_USER9 = CtEventKey::KeyCode_User9,
		ID_KEY_RESET = CtEventKey::KeyCode_Reset,
		ID_KEY_DISP_MODE = CtEventKey::KeyCode_DispCheck,
		ID_KEY_CODE_MAX
	}DbgCmndKeyCodeId;

	typedef enum _DBG_CMND_OD_ID {
		ID_OD_ALL,
		ID_OD_TSK,
		ID_OD_TBT,
		ID_OD_TRG,
		ID_OD_MPF,
		ID_OD_MPL,
		ID_OD_MBX,
		ID_OD_MAX
	}DbgCmndOdId;
	//★★★★★★★★★★★★★★★★★★★★
}

#endif
