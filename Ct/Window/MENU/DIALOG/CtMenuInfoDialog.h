/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/

#ifndef __CtMenuInfoDialog_H__
#define __CtMenuInfoDialog_H__

/*******************************************************************************
    インクルードファイル
*******************************************************************************/
//#include "CtObject.h"
#include "CtWindow.h"
#include "CtMenuInfo.h"

/*******************************************************************************
  定数の定義
*******************************************************************************/


/*******************************************************************************
  クラス宣言
*******************************************************************************/
class CtMenuInfoDialog : public CtObject
{
/*******************
  定数 
*******************/
public:
	typedef enum DialogDesignType {
		DialogDesignType_Version,
		DialogDesignType_OperationTime,
		DialogDesignType_UpdateConfirm,
	} DialogDesignType;

	typedef enum DialogTitleType {
		DialogTitleType_Under,
		DialogTitleType_Not,
	}DialogTitleType;

	typedef enum DialogContentType {
		DialogContentType_None,
		DialogContentType_Version,
		DialogContentType_Progress,
		DialogContentType_ParamSet,
	}DialogContentType;

	typedef struct DialogButtonInfo {
		bool				flag;
		CtFuncID            funcid;
		bool				bClose;
	} DialogLabelInfo;

	typedef struct CtMenuDialogInfo {
		CtWindowID				WindowId;
		DialogDesignType		Design;
		DialogTitleType			Title;
		GDI_STRING_ID           str_id;
		DialogContentType       cont;
		DialogButtonInfo        set;
		DialogButtonInfo        ret;
	} CtMenuDialogInfo;

/*******************
  メソッド 
*******************/
/* ---------------- 公開 ---------------------------------------------------- */
public:
	CtMenuInfoDialog() {};
	virtual ~CtMenuInfoDialog() {};

	static CtMenuDialogInfo* getDialogInfo(CtWindowID id);
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
	static CtMenuDialogInfo Info[];
	
/* ---------------- 非公開 -------------------------------------------------- */
protected :

};


#endif /* __CtMenuInfoDialog_H__ */
/**********************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
**********************************************************************************/
