/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/

#ifndef __CtMenuInfoSpinBox_H__
#define __CtMenuInfoSpinBox_H__

/*******************************************************************************
    インクルードファイル
*******************************************************************************/
//#include "CtObject.h"
#include "CtWindow.h"
#include "CtMenuInfo.h"

/*******************************************************************************
  定数の定義
*******************************************************************************/

#define FastInterval_SelectionTIme 10000
#define FastInterval_Max	10
#define FastInterval_Min	250

/*******************************************************************************
  クラス宣言
*******************************************************************************/
class CtMenuInfoSpinBox : public CtObject
{
/*******************
  定数 
*******************/
public:
	typedef enum SpinBoxAction {
		Action_Set,
		Action_Up,
		Action_Down,
		Action_Ret,
	}SpinBoxAction;

	typedef enum SpinBoxWfmMode {
		SpinBoxWfmMode_WAVE,
		SpinBoxWfmMode_VECTOR,
		SpinBoxWfmMode_ON,
		SpinBoxWfmMode_OFF,
	}SpinBoxWfmMode;

	typedef enum SpinBoxDesignType {
		SpinBoxDesignType_Normal,
		SpinBoxDesignType_Long,
		SpinBoxDesignType_LevelBar1,
		SpinBoxDesignType_LevelBar2,
		SpinBoxDesignType_LevelBar3,
	} SpinBoxDesignType;

	typedef enum SpinBoxActionType {
		SpinBoxActionType_Table,
		SpinBoxActionType_Value,
		SpinBoxActionType_CallFunc,
		SpinBoxActionType_Special,
		SpinBoxActionType_Frequency,
	} SpinBoxActionType;

	typedef enum SpinBoxTitleType {
		SpinBoxTitleType_None,
		SpinBoxTitleType_Menu,
		SpinBoxTitleType_Special,
	}SpinBoxTitleType;

	typedef enum SpinBoxDisplayType {
		SpinBoxDisplayType_Default,
		SpinBoxDisplayType_MenuTable,
	}SpinBoxDisplayType;

	typedef struct SpinBoxLabelInfo {
		SpinBoxDisplayType  type;
		char*               str;
		float               coef;
		int                 min;
		int                 max;
		int                 Offset;
		int                 step;
	} SpinBoxLabelInfo;

	typedef struct CtMenuSpinBoxInfo {
		CtWindowID			    WindowId;
		SpinBoxTitleType        Title;
		SpinBoxWfmMode          Wfm;
		SpinBoxDesignType       Design;
		SpinBoxActionType       action;
		int                     ParamId;
		SpinBoxLabelInfo        disp;
	} CtMenuSpinBoxInfo;

	typedef struct CtMenuSpinBoxTable {
		CtWindowID		WindowId;
		int				paramid;
		int				value;
		char*			str;
		GDI_STRING_ID	strid;
	}CtMenuSpinBoxTable;

/*******************
  メソッド 
*******************/
/* ---------------- 公開 ---------------------------------------------------- */
public:
	CtMenuInfoSpinBox() {};
	virtual ~CtMenuInfoSpinBox() {};

	static CtMenuSpinBoxInfo* getSpinBoxInfo(CtWindowID id);
	static CtMenuSpinBoxTable* getSpinBoxTable(CtWindowID id);

	static int getIntervalTime(CtWindowID id);

	static int getNumericMax(CtMenuSpinBoxInfo* pInfo);
	static int getNumericMin(CtMenuSpinBoxInfo* pInfo);

/* ---------------- 非公開 -------------------------------------------------- */
private :

/* ---------------- 非公開 -------------------------------------------------- */
protected :

/*******************
  メンバ 
*******************/
/* ---------------- 公開 ---------------------------------------------------- */
public:

/* ---------------- 非公開 -------------------------------------------------- */
private :
	static CtMenuSpinBoxInfo Info[];

	static CtMenuSpinBoxTable Table[];

/* ---------------- 非公開 -------------------------------------------------- */
protected :

};


#endif /* __CtMenuInfoSpinBox_H__ */
/**********************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
**********************************************************************************/
