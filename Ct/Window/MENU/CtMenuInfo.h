/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/

#ifndef __CtMenuInfo_H__
#define __CtMenuInfo_H__

/*******************************************************************************
    �C���N���[�h�t�@�C��
*******************************************************************************/
#include "CtObject.h"
#include "CtWindow.h"
#include "CtMenuInfoButtonId.h"
#include "CtEvent.h"

#include "AplParamService.h"
#include "str_id.h"
#include "string_api.h"

/*******************************************************************************
  �萔�̒�`
*******************************************************************************/

#define MENU_BUTTON_LINE 8		//�s��
#define MENU_LABEL_MIN_SIZA 75	//���̂̍ŏ��T�C�Y
#define MENU_VALUE_MIN_SIZA 100	//�ݒ�l�̍ŏ��T�C�Y
#define MENU_VALUE_MAX_SIZA 250	//�ݒ�l�̍ő�T�C�Y
#define MENU_LABEL_SIZE 39		//���̕����T�C�Y
#define MENU_BOLD_SIZE 1		//���̕��������T�C�Y
#define MENU_HISTORY_NUM 10		//���j���[�ő�K�w��

//11-70-19 ��������f�U�C��
//70->39
#define MENU_POP_TOP 11
#define MENU_POP_LABEL 70
#define MENU_POP_BOTTOM 19

#define MENU_POP_VTOP 11
#define MENU_POP_VLABEL 70
#define MENU_POP_VBOTTOM 19

/*******************************************************************************
  �N���X�錾
*******************************************************************************/
class CtMenuInfo : public CtObject
{
/*******************
  �萔 
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
		CtMenuWindowTitle title;        // �^�C�g�����
		CtMenuWindowChild child;        // �K�w���
	} CtMenuWindowInfo;

	typedef enum CtMenuButtonType {
		MenuButton_None          = 0x00,
		MenuButton_Default       = 0x01,    //����
		MenuButton_Value         = 0x02,    //�ݒ�l
		MenuButton_CheckBox      = 0x04,    //�`�F�b�N�{�b�N�X
		MenuButton_ParamLabel    = 0x08,    //ParamLabel
//		MenuButton_MaxLabel      = 0x10,    //�����ő�l
		MenuButton_NotButton     = 0x20,    //�\���̂�

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
    	bool valid;						// enum value���L����
        int value;                      // enum value
    } CtMenuExclution;

	typedef struct CtMenuValueInfo {
		int id;                         // param
		CtMenuValueDispType	type;	// �\�����
		float coef;						// Offset
		const char*   suffix;           // �Y����
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
		const char*			    str;        // ������
		GDI_STRING_ID           StringId;   // ������ID
		CtMenuButtonType        type;       // �{�^���\���^�C�v
		CtMenuExclution			exclution;	// �\���r���p���
		CtMenuValueInfo         value;      // �ݒ�l�\�����
		CtMenuActionInfo	    action;     // �{�^���������̓���
	} CtMenuButtonInfo;


	/*******************
  ���\�b�h 
*******************/
/* ---------------- ���J ---------------------------------------------------- */
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


/* ---------------- ����J -------------------------------------------------- */
private :
	static LANGUAGE_ID getLanguage(int value = -1);
	static LANGUAGE_ID getLanguage(GDI_STRING_ID STR_ID);

/* ---------------- ����J -------------------------------------------------- */
protected :

/*******************
  �����o 
*******************/
/* ---------------- ���J ---------------------------------------------------- */
public:

/* ---------------- ����J -------------------------------------------------- */
private :
	//Window���
	static CtMenuWindowInfo WindowInfo[];

	// Button���
    static CtMenuButtonInfo ButtonInfo[];

	/* ---------------- ����J -------------------------------------------------- */
protected :

};


#endif /* __CtMenuInfo_H__ */
/**********************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
**********************************************************************************/
