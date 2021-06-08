/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/

#ifndef __CtModeCheckFunction_H__
#define __CtModeCheckFunction_H__

#include "Ct.h"
#include "CtEvent.h"
#include "CtWidget.h"
#include "CtHLayout.h"
#include "CtVLayout.h"
#include "AplParamService.h"
#include "CtStackLabel.h"

class CtModeCheckFunction : public CtContainer
{
public:
	CtModeCheckFunction();
	virtual bool destroyWindow();
	virtual bool startupContainer();
	bool handleParamEvent(const CtEventParam& Param);
	bool handleButtonEvent(const CtEventButton& Button);
	bool handleKeyEvent(const CtEventKey& Key);
	CtLayout* createContainer();

protected :
	~CtModeCheckFunction();

private :
	CtLayout *m_pAll;
	CtLabel* m_pSdiOutFormatTitle;
	CtLabel* m_pSdiOutCharTitle;
	CtLabel* m_pSdiOutTitle;
	CtLabel* m_pVideoOutSel;
	CtLabel* m_pSdiOutFormat;
	CtLabel* m_pSdiOutChar;
	CtLabel* m_pSdiOut;
	bool updateSdiOut();
	
	CtLabel* m_pHdmiOutFormat;
	CtLabel* m_pHdmiOutChar;

	bool updateHdmiOutFormat(int int_Data);
	bool updateHdmiOutChar(int int_Data);

	

	CtLabel* m_pHdmiOut;
	bool updateHdmiOut(int int_Data);

	CtLabel* m_pLcdEvf;
	bool updateLcdEvf(int int_Data);

	CtLabel* m_pTotalRemain;
	bool updateTotalRemain();

	CtStackLabel* m_pStkSlot1Line;
	CtLabel* m_pSlot1Status;
	CtLabel* m_pSlot1RemainPer;
	CtLabel* m_pSlot1Remain;
	bool updateSlot1();

	CtStackLabel* m_pStkSlot2Line;
	CtLabel* m_pSlot2Status;
	CtLabel* m_pSlot2RemainPer;
	CtLabel* m_pSlot2Remain;
	bool updateSlot2();
};

#endif /* __CtMenuButtonList_H__ */

