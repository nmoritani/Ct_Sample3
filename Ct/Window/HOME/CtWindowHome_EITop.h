/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_007
 */


#ifndef __CtWindowHome_EITop_H__
#define __CtWindowHome_EITop_H__

#include "CtWindowCommon.h"
#include "CtWindowHome_EITop.h"

class CtWindowHome_EITop : public CtWindowMain
{
public:
	CtWindowHome_EITop();

    bool handleParamEvent(const CtEventParam& Param);
    bool handleButtonEvent(const CtEventButton& Button);
    bool handleKeyEvent(const CtEventKey& Key);
    bool handleTouchEvent(const CtEventTouch& Touch);
private:
	CtWindow* createWindow();
	CtWindow* m_pWin;
	
	void createNativeIsoValue();
	void create800IsoValue();
	void create2500IsoValue();
	void createGainValue();

	void setGainIsoDisp(int);
	void setGainDisp(bool);
	void setIsoDisp(bool);
		
	void setIsoSelect(int);
	void setGainSwitch(int);
	
	void setNativeIso(int);
	void set800BaseIso(int);
	void set2500BaseIso(int);
	void setGainSelect(int);
	
	CtLinkButton* m_pButtonUpperCenter;
	CtLinkButton* m_pButtonUpperLeft;

	CtColor m_ImageColor;
	CtColor m_LabelColor;
	CtColor m_LineColor;

	CtStackLabel* m_pStackLeftValueNativeISO;
	CtStackLabel* m_pStackLeftValue800BaseISO;
	CtStackLabel* m_pStackLeftValue2500BaseISO;
	CtStackLabel* m_pStackLeftValueGAIN;

	CtStackLabel* m_pUnitLabel;

	CtStackLabel* m_pStackCenterValueISO;
	CtStackLabel* m_pStackCenterValueGAIN;

	CtStackLabel* m_pStackLeftNameISO;
	CtLabel* m_pLabelLeftNameGAIN;

	CtStackLabel* m_pStackCenterNameISO_GAIN;
	
};

#endif
