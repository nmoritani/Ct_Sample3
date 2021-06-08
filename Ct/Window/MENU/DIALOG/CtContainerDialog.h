/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtListContainer
 */


#ifndef __CtContainerDialog_H__
#define __CtContainerDialog_H__

//#include "CtWindow.h"
#include "CtMenuInfoDialog.h"
//#include "AplParamService.h"
#include "CtContainerIndicateFrame.h"
#include "CtBuilderDialog.h"



class CtContainerDialog : public CtContainer
{
/*** 定数 ***************************************/
public:
protected:
private:
	typedef struct SetParamInfo {
		int				id;
		int             val;
	} SetParamInfo;


/*** メソッド ***********************************/
public:
	CtContainerDialog(CtWindowID id, CtWindowContents *pContents);
	virtual ~CtContainerDialog();
	bool destroyContainer();

	CtLayout* createContainer();

	bool handleButtonEvent(const CtEventButton& Button);
	bool handleKeyEvent(const CtEventKey& Key);

protected:

private:
	bool executionRet();
	bool executionSet();



/*** メンバ   ***********************************/
public:

protected:
	CtWindowID      m_WindowID;

	CtMenuInfoDialog::CtMenuDialogInfo m_Info;


	CtContainerIndicateFrame* m_pProgressBar;
	SetParamInfo	m_SetParam;
	CtWindowContents* m_pContents;
private:

};

#endif
