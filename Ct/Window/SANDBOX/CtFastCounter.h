/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWidgetControl
 */


#ifndef __CtFastCounter_H__
#define __CtFastCounter_H__

#include "CtContainer.h"
#include "CtLayout.h"
#include "CtStackLabel.h"

class CtFastCounter : public CtContainer {
public :
    CtFastCounter();
    virtual ~CtFastCounter();

	CtLayout* createContainer();
	bool destroyContainer();

	bool updateFastDraw();
	//	bool initialFastDraw();
	//	bool cleanupFastDraw();
	
protected:

private :
	int m_Counter;
	CtStackLabel *m_pLabel[4];
	int m_rank_1000;
	int m_rank_100;
	int m_rank_10;
	int m_rank_1;
};


#endif
