/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtKeyboad
 */


#ifndef __CtKeyboad_H__
#define __CtKeyboad_H__

#include "CtContainer.h"
#include "CtVLayout.h"
#include "CtHLayout.h"
#include "CtGridLayout.h"
#include "CtStackLabel.h"
#include "CtButton.h"
#include "CtTextField.h"
#include "CtToggleButton.h"

class CtKeyboad : public CtContainer {
public :
    CtKeyboad();

    virtual ~CtKeyboad();

	CtLayout* createContainer();
	bool destroyContainer();

	//	bool handleEvent(CtWidget* pButton, const CtEvent& Event);
	bool handleButtonEvent(const CtEventButton& Button);
	
protected:

private :
	CtStackLabel* m_pKeyboad;
	CtGridLayout* m_pCurrent;
	
	CtTextField *m_pText;
#if 0
	CtButton *m_pKomoji;
	CtButton *m_pKigou;
#else
	CtToggleButton *m_pKomoji;
	CtToggleButton *m_pKigou;
#endif
	CtButton *m_pBS;
	CtButton *m_pRet;
	CtButton *m_pEnter;
	CtButton *m_pLeft;
	CtButton *m_pRight;
	CtButton *m_pSpace;
	
	CtVLayout *m_pBox;
};


#endif
