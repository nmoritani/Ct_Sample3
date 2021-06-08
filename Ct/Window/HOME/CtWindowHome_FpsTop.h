/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_007
 */


#ifndef __CtWindowHome_FpsTop_H__
#define __CtWindowHome_FpsTop_H__

#include "CtWindowCommon.h"

class CtWindowHome_FpsTop : public CtWindowMain
{
public:
	CtWindowHome_FpsTop();

	bool handleParamEvent(const CtEventParam& Param);
    bool handleButtonEvent(const CtEventButton& Button);
    bool handleKeyEvent(const CtEventKey& Key);
    bool handleTouchEvent(const CtEventTouch& Touch);
private:
	CtWindow* createWindow();
	CtColor m_ImageColor;
	CtColor m_LabelColor;
	CtColor m_LineColor;
	CtWindow* m_pWin;

	// ValueílÇ∆OFFÇÃêÿä∑Ç¶
	CtStackLabel* m_pUpperLeftValue;
	// Valueï\é¶óp
	CtLabel* m_pLeftFreqValue;
	CtLabel* m_pLeftVfrValue;

	// ON/OFF
	CtStackLabel* m_pStackUpperCenterValue;
	CtButton* m_pBtnUpperCenter;
	
	// Shutterí≤êÆâÊñ 
	CtLinkButton* m_pBtnUpperLeft;
	//CtButton* m_pBtnUpperCenter;
	
	void setVfrSwitch(int);
	void setFreqDisp(int);
	void createFpsValue();
	void setVfrValue();
};

#endif
