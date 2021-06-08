/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/

#ifndef __CtMenuInfoDialog_H__
#define __CtMenuInfoDialog_H__

/*******************************************************************************
    �C���N���[�h�t�@�C��
*******************************************************************************/
//#include "CtObject.h"
#include "CtWindow.h"
#include "CtMenuInfo.h"

/*******************************************************************************
  �萔�̒�`
*******************************************************************************/


/*******************************************************************************
  �N���X�錾
*******************************************************************************/
class CtMenuInfoDialog : public CtObject
{
/*******************
  �萔 
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
  ���\�b�h 
*******************/
/* ---------------- ���J ---------------------------------------------------- */
public:
	CtMenuInfoDialog() {};
	virtual ~CtMenuInfoDialog() {};

	static CtMenuDialogInfo* getDialogInfo(CtWindowID id);
/* ---------------- ����J -------------------------------------------------- */
private :

/* ---------------- ����J -------------------------------------------------- */
protected :

/*******************
  �����o 
*******************/
/* ---------------- ���J ---------------------------------------------------- */
public:

/* ---------------- ����J -------------------------------------------------- */
private :
	static CtMenuDialogInfo Info[];
	
/* ---------------- ����J -------------------------------------------------- */
protected :

};


#endif /* __CtMenuInfoDialog_H__ */
/**********************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
**********************************************************************************/
