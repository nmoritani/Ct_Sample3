/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:	CtScrollBar
*/


#ifndef __CtScrollBar_H__
#define __CtScrollBar_H__

#include "Ct.h"
#include "CtLayout.h"

class CtScrollBar : public CtLayout {
public:
	CtScrollBar(CtLabel* pBase, CtLabel* pSlider, int MinSliderSize = 1);
	CtScrollBar(CtLabel* pBase, CtLabel* pSlider, CtMargin EdgeMargin, int MinSliderSize = 1);

	virtual ~CtScrollBar();

	bool isMaximum();
	bool isMinimum();
	int getMaximum();
	int getMinimum();
	int getValue();
	void setMaximum(int Maximum);
	void setMinimum(int Minimum);
	void setValue(int Value);
	void setOrientation(bool isHorizontal);

	bool handleTouchEvent(const CtEventTouch & Event);
	//void setRegion(const CtRegion& Region);
	bool setRegion(const CtRegion& Region);

protected:
	// 呼ばれたくない関数をpublic->protectedへ変更
	bool addWidget(CtWidget* pWidget, CtAlign Align = AlignCenter);
	bool addWidget(CtWidget* pWidget, CtMargin Margin, CtAlign Align = AlignCenter);
	bool addWidget(CtWidget* pWidget, int Stretch);
	bool addWidget(CtWidget* pWidget, CtAlign Align, int Stretch);
	bool addWidget(CtWidget* pWidget, CtMargin Margin, int Stretch);
	bool addWidget(CtWidget* pWidget, CtMargin Margin, CtAlign Align, int Stretch);
	bool addWidget(CtWidget* pWidget, CtSize Size, CtAlign Align = AlignCenter);
	bool swapWidget(CtWidget* pWidget, int Index, CtAlign Align = AlignCenter);
	bool swapWidget(CtWidget* pWidget, int Index, CtMargin Margin, CtAlign Align = AlignCenter);
	bool swapWidget(CtWidget* pWidget, CtWidget* dst_pWidget, CtAlign Align = AlignCenter);
	bool swapWidget(CtWidget* pWidget, CtWidget* dst_pWidget, CtMargin Margin, CtAlign Align = AlignCenter);

private:
	void init();
	void updateSlider();
	int getValueByPos(short x, short y);
	int getEffectiveBaseLength();
	//void adjustSliderPos(CtRegion &slider, CtRegion &base);

	bool TouchAction_Press(short _x, short _y);
	void TouchAction_Release();
	bool TouchAction_Slide(CtEventTouchSlide & _slide);

private:
	/* instance */
	CtWidget* m_pBase;		//!< ベースのバー部分
	CtWidget* m_pSlider;	//!< スライダー部分

	/* property */
	CtMargin m_Margin;
	int m_Minimum;
	int m_Maximum;
	int m_Value;
	int m_MinSliderSize;
	
	bool m_NeedChangeSliderSize;
	bool m_IsHorizontal;
	bool m_IsAction;
	

};


#endif
