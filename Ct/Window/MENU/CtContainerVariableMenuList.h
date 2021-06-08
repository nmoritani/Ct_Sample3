/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			_CtContainerVariableMenuList
 */


#ifndef __CtContainerVariableMenuList_H__
#define __CtContainerVariableMenuList_H__

#include "CtContainer.h"
#include "CtWindowCommon.h"
#include "CtMenuButton.h"
#include "CtMenuListView.h"

#include "CtContainerMenuTitle.h"
#include "CtContainerCtrlButton.h"

class CtContainerVariableMenuList : public CtContainer
{
public :

    CtContainerVariableMenuList( CtWindowID id );

    virtual ~CtContainerVariableMenuList();
	bool destroyContainer();

	CtLayout* createContainer();

	bool handleButtonEvent(const CtEventButton& Button);
    bool handleKeyEvent(const CtEventKey& Key);

	void addButton(CtButton* pButton);
	void updateEnd();

	void setCurrentIndex(int index);

    void cleanupList();

protected:

private :

    void update_PageNo();


public:

protected:

private:

    CtWindowID				m_WindowID;

    CtLabel*				m_pPage;

    CtMenuListView*			m_pList;

	unsigned long			m_Max;

	int						m_Current;

	CtContainerCtrlButton*	m_pCtrl;
};

#endif
