/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/

#ifndef __CtModeCheckSwitch_H__
#define __CtModeCheckSwitch_H__

#include "Ct.h"
#include "CtEvent.h"
#include "CtWidget.h"
#include "CtHLayout.h"
#include "CtVLayout.h"
#include "AplParamService.h"
#include "CtStackLabel.h"

class CtModeCheckSwitch : public CtContainer
{
public:
	CtModeCheckSwitch();
	virtual bool destroyWindow();
	virtual bool startupContainer();

	bool handleParamEvent(const CtEventParam& Param);
	bool handleButtonEvent(const CtEventButton& Button);
	bool handleKeyEvent(const CtEventKey& Key);
	CtLayout* createContainer();
protected :
	~CtModeCheckSwitch();

private :
	////////////////////////////
	CtLabel* m_pUser1;
	CtLabel* m_pUser2;
	CtLabel* m_pUser3;
	CtLabel* m_pUser4;
	CtLabel* m_pUser5;
	CtLabel* m_pUser6;
	CtLabel* m_pUser7;

	bool updateUserSw(int t_Data, CtLabel*& pUserSwNo);
	////////////////////////////
	CtLabel* m_pGainL;
	bool updateGainSwLow(int int_Data);
	CtLabel* m_pGainM;
	bool updateGainSwMid(int int_Data);
	CtLabel* m_pGainH;
	bool updateGainSwHigh(int int_Data);
	CtLabel* m_pS_Gain;
	bool updateS_Gain(int int_Data);
	////////////////////////////
	CtLabel* m_pWbA;
	CtLabel* m_pWbB;
	CtLabel* m_pWbPrst;
	bool updateWBSw();
	////////////////////////////
	CtLayout *m_pAll;

};

#endif /* __CtMenuButtonList_H__ */

