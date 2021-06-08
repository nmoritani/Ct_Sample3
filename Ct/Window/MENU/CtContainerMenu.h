/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtListContainer
 */


#ifndef __CtContainerMenu_H__
#define __CtContainerMenu_H__

#include "CtWindowCommon.h"
#include "CtMenuInfo.h"
#include "CtMenuBuilder.h"
#include "CtContainerCtrlButton.h"
#include "CtList.h"

class CtContainerMenu : public CtContainer {
public :


	CtContainerMenu(CtWindowID _id, CtWindowContents* pContents);

    virtual ~CtContainerMenu();
	virtual bool destroyContainer();

	bool handleParamEvent(const CtEventParam& Param);
	bool handleButtonEvent(const CtEventButton& Button);
	bool handleKeyEvent(const CtEventKey& Key);
	bool handleTouchEvent(const CtEventTouch& Touch);

	CtLayout* createContainer();

	CtListView* getMenuList() const;

private:
	void checkPage();
	bool checkParentState();

private:
	CtWindowID      m_WindowID;
	CtListView*     m_pMenuList;

	int m_OldWidth;
	int m_RetWidth;

	int m_ParentParam;
	int m_ParentValue;

protected:

private :
	CtContainerCtrlButton* m_pCtrl;

};


#endif
