/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtBuilderDialog
 */


#ifndef __CtBuilderDialog_H__
#define __CtBuilderDialog_H__

#include "CtWindowCommon.h"
#include "CtMenuInfoDialog.h"
//#include "CtContainerDialog.h"
#include "CtWindowContentsVersionDisp.h"
#include "CtContainerIndicateFrame.h"

#include "CtContainerCtrlButton.h"
#include "CtContainerMenuTitle.h"



#define LabelFont               CtFontSet(FontTypeNormal_alignRight, CtColor::White)
//#define ValueFont               CtFontSet(FontTypeNormal, CtColor::White)
#define ValueFont               CtFontSet(FontTypeNormal_alignAuto, CtColor::White)

class CtBuilderDialog : public CtObject
{
/*** 定数 ***************************************/
public:
protected:
	typedef struct DialogInfo {
		unsigned char version[Version_Size];
	} DialogInfo;

private:

/*** メソッド ***********************************/
public:
	CtBuilderDialog(CtWindowID id);
	~CtBuilderDialog();

	CtLayout* createContainer(CtWindowContents* pContents);

protected:
	CtLayout* createLayout();

	CtLayout* createMain();


	CtLayout* createVersion();
	CtLayout* createOperationTime();
	CtLayout* createUpdateConfirm();

private:

	void setContents(CtWindowContents* pContents);
	bool convertVersionInfo(int Value, char *Data);


/*** メンバ   ***********************************/
public:

protected:
	CtWindowID					m_WindowId;
	DialogInfo                  m_Content;

private:

};

#endif
