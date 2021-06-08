/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_007
 */


#ifndef __CtWindowHome_ShutterTop_H__
#define __CtWindowHome_ShutterTop_H__

#include "CtWindowCommon.h"

class CtWindowHome_ShutterTop : public CtWindowMain
{
public:
	CtWindowHome_ShutterTop();
    
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

	// Value値とOFFの切換え
	CtStackLabel* m_pUpperLeftValue;
	// Value表示用
	CtLabel* m_pLeftValue;

	// ON/OFF
	CtStackLabel* m_pStackUpperCenterValue;
	CtButton* m_pBtnUpperCenter;
	
	// Shutter調整画面
	CtLinkButton* m_pBtnUpperLeft;
	//CtButton* m_pBtnUpperCenter;
	
	void setShutterSwitch(int);
	void setShutterDisp(int);
	void createShutterValue();
	void setShutterValue();
};

#endif
