/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/

#ifndef __CtMenuInfo_H__
#define __CtMenuInfo_H__

/*******************************************************************************
    インクルードファイル
*******************************************************************************/
#include "CtObject.h"
#include "CtWindow.h"
#include "CtMenuInfoButtonId.h"
#include "CtEvent.h"

#include "AplParamService.h"
#include "str_id.h"
#include "string_api.h"

/*******************************************************************************
  定数の定義
*******************************************************************************/

#define MENU_BUTTON_LINE 8		//行数
#define MENU_LABEL_MIN_SIZA 75	//名称の最小サイズ
#define MENU_VALUE_MIN_SIZA 100	//設定値の最小サイズ
#define MENU_VALUE_MAX_SIZA 250	//設定値の最大サイズ
#define MENU_LABEL_SIZE 39		//名称文字サイズ
#define MENU_BOLD_SIZE 1		//名称文字太さサイズ
#define MENU_HISTORY_NUM 10		//メニュー最大階層数

//11-70-19 松原さんデザイン
//70->39
#define MENU_POP_TOP 11
#define MENU_POP_LABEL 70
#define MENU_POP_BOTTOM 19

#define MENU_POP_VTOP 11
#define MENU_POP_VLABEL 70
#define MENU_POP_VBOTTOM 19

/*******************************************************************************
  クラス宣言
*******************************************************************************/
class CtMenuInfo : public CtObject
{
/*******************
  定数 
*******************/
public:
	typedef enum CtMenuWindowType {
		WINDOW_TYPE_LIST,
		WINDOW_TYPE_CHECKLIST,
		WINDOW_TYPE_POPLIST,
		WINDOW_TYPE_SPINBOX,
		WINDOW_TYPE_TIMESETTING,
		WINDOW_TYPE_WORLD,
		WINDOW_TYPE_DIALOG,
		WINDOW_TYPE_KEYBOARD,
		WINDOW_TYPE_2LIST,
		WINDOW_TYPE_TC,
		WINDOW_TYPE_UB,
		WINDOW_TYPE_FILE,
		WINDOW_TYPE_AREASETTING,

		WINDOW_TYPE_WINDOW,
		WINDOW_TYPE_SKIP,
		WINDOW_TYPE_MAX,
	} CtMenuWindowType;

	typedef enum CtMenuTitleType {
		TitleType_None,
		TitleType_Default,
		TitleType_SetPhase,
		TitleType_Set,
		TitleType_Phase,

		TitleType_Max
	}CtMenuTitleType;

	typedef struct CtMenuWindowTitle {
		CtMenuTitleType type;
		unsigned char   num;
		unsigned int    id[MENU_HISTORY_NUM];
	} CtMenuWindowTitle;

	typedef struct CtMenuWindowChild {
		unsigned char num;
		unsigned int id[160];
	} CtMenuWindowChild;

	typedef struct CtMenuWindowInfo {
		CtWindowID  id;                 // WindowId
		CtMenuWindowType type;          // WindowType
		CtMenuWindowTitle title;        // タイトル情報
		CtMenuWindowChild child;        // 階層情報
	} CtMenuWindowInfo;

	typedef enum CtMenuButtonType {
		MenuButton_None          = 0x00,
		MenuButton_Default       = 0x01,    //名称
		MenuButton_Value         = 0x02,    //設定値
		MenuButton_CheckBox      = 0x04,    //チェックボックス
		MenuButton_ParamLabel    = 0x08,    //ParamLabel
//		MenuButton_MaxLabel      = 0x10,    //横幅最大値
		MenuButton_NotButton     = 0x20,    //表示のみ

		MenuButton_InfoLabel     = MenuButton_Value | MenuButton_NotButton,
		MenuButton_CheckBoxParam = MenuButton_CheckBox | MenuButton_ParamLabel ,
	}CtMenuButtonType;

	typedef enum _CtMenuValueDispType {
		ValueType_StackLabel  = 0x0001,
		ValueType_Number      = 0x0002,
		ValueType_IpAddress   = 0x0003,
		ValueType_String      = 0x0004,
		ValueType_Special     = 0x0005,
		ValueType_Omit        = 0x0006,
		ValueType_Unknown     = 0x0007,
		ValueType_Mask        = 0x00FF,

		ValueType_SizeAuto    = 0x0000,
		ValueType_Size150     = 0x0100,
		ValueType_Size200     = 0x0200,
		ValueType_SizeMAX     = 0x0300, //250
		ValueType_SizePlus    = 0x0400,
		ValueType_SizeMask    = 0xFF00,

		ValueType_FileName    = ValueType_Special | ValueType_Size200,
		ValueType_Ip          = ValueType_IpAddress | ValueType_Size150,
		ValueType_OmitLabel   = ValueType_Omit | ValueType_Size150,
		ValueType_MacAddress  = ValueType_String | ValueType_Size200,
		ValueType_Format      = ValueType_StackLabel | ValueType_Size200,
		ValueType_SpecialPlus = ValueType_Special | ValueType_SizePlus,

	} CtMenuValueDispType;

	typedef enum _CtMenuActionType {
		CtMenuAction_Default,
		CtMenuAction_Switch,
		CtMenuAction_Confirm,
		CtMenuAction_NotContents,
	} CtMenuActionType;

	typedef struct CtMenuExclution {
        int id;                         // param
    	bool valid;						// enum valueが有効か
        int value;                      // enum value
    } CtMenuExclution;

	typedef struct CtMenuValueInfo {
		int id;                         // param
		CtMenuValueDispType	type;	// 表示種別
		float coef;						// Offset
		const char*   suffix;           // 添え字
		bool plus;
	} CtMenuValueInfo;

	typedef struct CtMenuActionInfo {
		CtMenuActionType		Type;
		AplParamEepromId        ParamID;    // AplParam
		int	                    SubItem;    // SubItem
		CtFuncID                FuncID;		// FuncID
		CtEventWindow::WinCmd   OpenType;   // OpenType
		CtWindowID              WindowID;   // WindowID
	} CtMenuActionInfo;


	typedef struct CtMenuButtonInfo {
		CtMenuButtonId          id;
		const char*			    str;        // 文字列
		GDI_STRING_ID           StringId;   // 文字列ID
		CtMenuButtonType        type;       // ボタン表示タイプ
		CtMenuExclution			exclution;	// 表示排他用情報
		CtMenuValueInfo         value;      // 設定値表示情報
		CtMenuActionInfo	    action;     // ボタン押下時の動作
	} CtMenuButtonInfo;


	/*******************
  メソッド 
*******************/
/* ---------------- 公開 ---------------------------------------------------- */
public:
	CtMenuInfo() {};
	virtual ~CtMenuInfo() {};

    /* Button */
	static CtMenuButtonInfo* getButtonInfoAll();
	static CtMenuButtonInfo* getButtonInfo(int id);
	static CtMenuExclution* getButtonExclution(int id);
	static CtMenuActionInfo* getButtonAction(int ButtonId);

	static const unsigned short* getButtonString(CtMenuButtonInfo* pInfo);
	static CtFontSet getLabelFont(CtMenuButtonInfo* pInfo);
	static CtFontSet getValueFont(CtMenuButtonInfo* pInfo);

    /* Window */
	static CtMenuWindowInfo* getWindowInfo(CtWindowID id);
	static CtMenuWindowTitle* getWindowTitle(CtWindowID id);
	static CtMenuWindowChild* getWindowChild(CtWindowID id);
	static CtMenuWindowType getWindowType(CtWindowID id);

	static void getMenuSize(CtWindowID id, short& label, short& value, bool& bArrow);
	static short getHierarchy(CtWindowID id);
	static bool checkArrow(CtMenuButtonInfo* pButtonInfo);
	static int getParamValue(int id);
	static bool checkExit(CtWindowID id);

	static CtColor getMenuBackColor();

	/* Other */
	static short getStringSize(GDI_STRING_ID id);
	static short getStringSize(GDI_STRING_ID id, CtFontSet fSet);
	static short getStringSize(const char* str);
	static short getStringSize(const char* str, CtFontSet fSet);
	static short getStringSize(const unsigned short*);
	static short getStringSize(const unsigned short*, CtFontSet fSet);

	static void getParentId(CtWindowID Windowid, int& param, int& value);


/* ---------------- 非公開 -------------------------------------------------- */
private :
	static LANGUAGE_ID getLanguage(int value = -1);
	static LANGUAGE_ID getLanguage(GDI_STRING_ID STR_ID);

/* ---------------- 非公開 -------------------------------------------------- */
protected :

/*******************
  メンバ 
*******************/
/* ---------------- 公開 ---------------------------------------------------- */
public:

/* ---------------- 非公開 -------------------------------------------------- */
private :
	//Window情報
	static CtMenuWindowInfo WindowInfo[];

	// Button情報
    static CtMenuButtonInfo ButtonInfo[];

	/* ---------------- 非公開 -------------------------------------------------- */
protected :

};


#endif /* __CtMenuInfo_H__ */
/**********************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
**********************************************************************************/
