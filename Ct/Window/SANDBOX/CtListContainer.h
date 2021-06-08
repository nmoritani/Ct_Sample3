/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWidgetControl
 */


#ifndef __CtListContainer_H__
#define __CtListContainer_H__

#include "CtContainer.h"
#include "CtListView.h"
#include "CtButton.h"

class CtListContainer : public CtContainer {
public :
    CtListContainer();

    virtual ~CtListContainer();

	CtLayout* createContainer();

	bool handleButtonEvent(const CtEventButton& Event);
	
protected:

private :
	CtListView *m_pList;
	CtButton *m_pButtonPageUp;
	CtButton *m_pButtonPageDown;
	CtButton *m_pButtonLineUp;
	CtButton *m_pButtonLineDown;
	CtLabel  *m_pTest;
	int m_testcnt;
};


#endif
