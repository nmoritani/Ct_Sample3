/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/

#ifndef __CtKeyboardInfo_H__
#define __CtKeyboardInfo_H__

#include "CtObject.h"
#include "CtWindow.h"

 /*******************************************************************************
 定数の定義
 *******************************************************************************/
 /* WINDOW */
#define MENU_WINDOW_SIZE_X	0
#define MENU_WINDOW_SIZE_Y	0
#define MENU_WINDOW_SIZE_W	960
#define MENU_WINDOW_SIZE_H	640

 /* COMMON */
#define KEYBOARD_H_SIZE_SPACE1		13
#define KEYBOARD_H_SIZE_TEXT		78
#define KEYBOARD_H_SIZE_SPACE2		37
#define KEYBOARD_H_SIZE_LINE		78
#define KEYBOARD_H_SIZE_LINE_SPACE	35
#define KEYBOARD_H_SIZE_KEYBOARD	78 + 35 + 78 + 35 + 78 + 35 + 78
#define KEYBOARD_H_SIZE_SPACE3		14

/* Button */
#define BUTTON_W		76
#define BUTTON_W_L		124
#define BUTTON_W_B		78
#define BUTTON_H		78

 /* KEYBOARD */
#define TEXTBOX_SPACE_H		23
#define TEXTBOX_AREA_H		78
#define TEXTBOX_TITLE_W		216
#define TEXTBOX_BOX_W		600
#define TEXTBOX_BOX_SPACE	MENU_WINDOW_SIZE_W - TEXTBOX_TITLE_W - TEXTBOX_BOX_W

#define KEYBOARD_BUTTON_H			78
#define KEYBOARD_BUTTON_W			76
#define KEYBOARD_BUTTON_MARGINE_H	32
#define KEYBOARD_AREA_H		KEYBOARD_BUTTON_H + KEYBOARD_BUTTON_MARGINE_H + KEYBOARD_BUTTON_H + KEYBOARD_BUTTON_MARGINE_H + KEYBOARD_BUTTON_H + KEYBOARD_BUTTON_MARGINE_H + KEYBOARD_BUTTON_H
#define KEYBOARD_AREA_SPACE		14
#define KEYBOARD_AREA_SPACE2_1	61
#define KEYBOARD_AREA_SPACE2_2	63
#define KEYBOARD_AREA_BUTTON_SPACE	19



 /*******************************************************************************
 クラス宣言
 *******************************************************************************/
class CtKeyboardInfo : public CtObject
{
public:
	typedef enum Alphabet {
		Q, W, E, R, T, Y, U, I, O, P,
		 A, S, D, F, G, H, J, K, L,
		  Z, X, C, V, B, N, M,
		Alphabet_End,
	}Alphabet;
	
	typedef enum CtKeyboardType {
		KeyboardType_Full,
		KeyboardType_Alpha, // AlphabetOnly
		KeyboardType_Number,
		KeyboardType_Ip,
		KeyboardType_IpV6,
		KeyboardType_PassWord,
		KeyboardType_FileName,
	}CtKeyboardType;

	typedef enum CtTextType {
		TextType_Default,
		TextType_Number0,
		TextType_Number,
		TextType_Ip,
		TextType_IpV6,
		TextType_File,
		TextType_Special,
//		TextType_Port,
		TextType_None,
	}CtTextType;

	typedef enum CtExcclusionType {
		ExcclusionType_Default,
		ExcclusionType_Ip,
		ExcclusionType_Number,
		ExcclusionType_PassWord,
		ExcclusionType_UserPassWord,
		ExcclusionType_Port,
		ExcclusionType_Range,
		ExcclusionType_Freedom,
	}CtExcclusionType;

	typedef enum CtActionType {
		ActionType_Default,
		ActionType_Transfer,
		ActionType_Function,
		ActionType_Special,
	}CtActionType;

	typedef struct CtKeyboardActionInfo {
		CtActionType        Type;
		CtFuncID            FuncID;
		CtOpenType          OpenType;
		CtWindowID			WindowId;
	} CtKeyboardActionInfo;

	typedef struct CtKeyboardInfoItem {
		CtWindowID			    WindowId;	// 対象のWindowID
		const char*             str;        // 文字列
		GDI_STRING_ID		    StringId;   // 文字列ID
		AplParamEepromId	    ParamId;    // AplParam
		int					    Size;       // 入力サイズ
		CtKeyboardType		    Type;       // KeyBoardType
		CtTextType		        Text;       // TextType
		CtExcclusionType		Exclusion;  // TitelType
		CtKeyboardActionInfo	action;     // ActionInfo
	} CtKeyboardInfoItem;


/*** メソッド ***********************************/
public:
	static const unsigned int KEYBOARD_LINE1_NUM;
	static const unsigned int KEYBOARD_LINE2_NUM;
	static const unsigned int KEYBOARD_LINE3_NUM;
	CtKeyboardInfo() {};
	virtual ~CtKeyboardInfo() {};

	static CtKeyboardInfoItem* getKeyboardInfo(CtWindowID id);
private :

private :
	static CtKeyboardInfoItem Info[];
};
const unsigned int KEYBOARD_LINE1_NUM = 10;
const unsigned int KEYBOARD_LINE2_NUM = 9;
const unsigned int KEYBOARD_LINE3_NUM = 7;


#endif /* __CtKeyboardInfo_H__ */
/**********************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
**********************************************************************************/
