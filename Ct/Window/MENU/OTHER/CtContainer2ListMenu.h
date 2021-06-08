/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtListContainer
 */


#ifndef __CtContainer2ListMenu_H__
#define __CtContainer2ListMenu_H__

#include "CtWindowCommon.h"
#include "CtMenuButton.h"
#include "Ct2ListView.h"
#include "CtMenuInfo.h"
#include "CtContainerCtrlButton.h"
#include "CtContainerMenuTitle.h"

class CtContainer2ListMenu : public CtContainer {
public :


	CtContainer2ListMenu(CtWindowID _id);

    virtual ~CtContainer2ListMenu();
	virtual bool destroyContainer();

	bool handleParamEvent(const CtEventParam& Param);
	bool handleButtonEvent(const CtEventButton& Button);
	bool handleKeyEvent(const CtEventKey& Key);

	CtLayout* createContainer();
	virtual bool startupContainer();

private:
	CtLayout* createList();
	CtLayout* createButton(unsigned int index);

	bool checkPage();


private:
	CtWindowID      m_WindowID;
	Ct2ListView*		m_pMenuList;



protected:

private :
	CtContainerCtrlButton* m_pCtrl;

};


#endif
