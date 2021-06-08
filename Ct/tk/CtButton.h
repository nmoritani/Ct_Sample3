/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:	CtButton
 */


#ifndef __CtButton_H__
#define __CtButton_H__

#include "Ct.h"
#include "CtStackLabel.h"

//class CtEvent;

class CtButton : public CtStackLabel {
private:
	enum {
		CT_BUTTON_LONG_TIMER_ID,
		CT_BUTTON_REPEAT_TIMER_ID
	};
public :
	#define LabelMargin CtMargin(5,5,5,5)
	
	enum Shape {
		RoundRect,
		Rect,
		Ellipse,
		Line,
		None
	};

	enum State {
		StateInvalid = 0,
		StateNormal,
		StateFocused,
		StatePressed,
		StateSilentFocused,
		StateNone,
		StateAll,

		StateMax = StateNone
	};


    CtButton();
    CtButton(CtButton::Shape Shape);
	CtButton(const CtSize& Size, CtButton::Shape Shape = RoundRect);
	CtButton(const CtRegion& Region, CtButton::Shape Shape = RoundRect);

    CtButton(const GDI_IMAGE_ID ImageID, CtButton::Shape Shape = RoundRect);
    CtButton(const GDI_IMAGE_ID ImageID, const CtColor& fillColor, CtButton::Shape Shape = RoundRect);
    CtButton(const GDI_IMAGE_ID ImageID, const CtColor& fillColor, const CtColor& edgeColor, CtButton::Shape Shape = RoundRect);
	CtButton(const GDI_HANDLER DrawableID, CtButton::Shape Shape = RoundRect);
    CtButton(const GDI_STRING_ID StringID, const CtFontSet& FontSet, CtButton::Shape Shape = RoundRect);
    CtButton(const GDI_STRING_ID StringID, CtButton::Shape Shape = RoundRect);
	CtButton(const char* ucStr, const CtFontSet& FontSet, CtButton::Shape Shape = RoundRect);
	CtButton(const char* ucStr, CtButton::Shape Shape = RoundRect);
	CtButton(const unsigned short* ucStr, const CtFontSet& FontSet, CtButton::Shape Shape = RoundRect);
	CtButton(const unsigned short* ucStr, CtButton::Shape Shape = RoundRect);
	CtButton(CtLabel *pLabel, CtButton::Shape Shape = RoundRect);
    CtButton(CtLayout *pLayout, CtButton::Shape Shape = RoundRect);
	
    CtButton(const CtSize& Size, const GDI_IMAGE_ID ImageID, CtButton::Shape Shape = RoundRect);
    CtButton(const CtSize& Size, const GDI_IMAGE_ID ImageID, const CtColor& fillColor, CtButton::Shape Shape = RoundRect);
    CtButton(const CtSize& Size, const GDI_IMAGE_ID ImageID, const CtColor& fillColor, const CtColor& edgeColor, CtButton::Shape Shape = RoundRect);
	CtButton(const CtSize& Size, const GDI_HANDLER DrawableID, CtButton::Shape Shape = RoundRect);
    CtButton(const CtSize& Size, const GDI_STRING_ID StringID, const CtFontSet& FontSet, CtButton::Shape Shape = RoundRect);
    CtButton(const CtSize& Size, const GDI_STRING_ID StringID, CtButton::Shape Shape = RoundRect);
	CtButton(const CtSize& Size, const char* ucStr, const CtFontSet& FontSet, CtButton::Shape Shape = RoundRect);
	CtButton(const CtSize& Size, const char* ucStr, CtButton::Shape Shape = RoundRect);
	CtButton(const CtSize& Size, const unsigned short* ucStr, const CtFontSet& FontSet, CtButton::Shape Shape = RoundRect);
	CtButton(const CtSize& Size, const unsigned short* ucStr, CtButton::Shape Shape = RoundRect);
	CtButton(const CtSize& Size, CtLabel *pLabel, CtButton::Shape Shape = RoundRect);
    CtButton(const CtSize& Size, CtLayout *pLayout, CtButton::Shape Shape = RoundRect);
	virtual ~CtButton();
	
	bool setButtonShape(CtButton::Shape Shape, short Width = -1);
#if 0
	bool setTop(CtLabel* pLabel, CtMargin Margin = LabelMargin, CtAlign Align = AlignCenter);
	bool setTop(CtLayout* pLayout, CtMargin Margin = LabelMargin, CtAlign Align = AlignCenter);
	bool setTopMargin(CtMargin Margin, CtAlign Align);
	bool setTopMargin(CtAlign Align);
	CtWidget *getTop();

    bool setBase(const GDI_IMAGE_ID ImageID);
	bool setBase(const GDI_HANDLER DrawableID);
#else
	bool setTop(CtLabel* pLabel, CtMargin Margin, CtAlign Align = AlignCenter);
	bool setTop(CtLabel* pLabel, CtAlign Align = AlignCenter);
	bool setTop(CtLayout* pLayout, CtMargin Margin, CtAlign Align = AlignCenter);
	bool setTop(CtLayout* pLayout, CtAlign Align = AlignCenter);
	bool setElement(CtButton::State State, CtWidget* pWidget, CtMargin Margin, CtAlign Align = AlignCenter);
	bool setElement(CtButton::State State, CtWidget* pWidget, CtAlign Align = AlignCenter);
#endif
	virtual bool handleTouchEvent(const CtEventTouch& Touch);
	virtual bool handleKeyEvent(const CtEventKey& Key);
	virtual bool handleTimerEvent(const CtEventTimer& Timer);

	bool setFocusable(bool bFocusable);
	bool isFocusable() const;

	bool isFocused() const;
	virtual bool setFocus(bool bSilent = false);
	virtual bool cancelFocus();
	
	bool isPressed() const;
	bool setPressed();
	bool cancelPressed();

	bool isInvalid() const;
	bool setInvalid(bool bInvalid);
    virtual bool setVisible(bool bVisible);
	
	bool setDialIndex(int Index);
	inline int getDialIndex() const;

	virtual bool isButton() const;

	bool setImage(const GDI_IMAGE_ID ImageID);
	bool setImage(const GDI_IMAGE_ID ImageID, const CtColor& fillColor, const CtColor& edgeColor);
	bool setImage(short Width, short Height, short BufWidth, short BufHeight, const unsigned char* Data, CtImageType Type);
	bool setImage(short Width, short Height, short YPlaneSize, short PlaneStride, short PlaneHeight, const unsigned char* pYPlane, const unsigned char* pCPlane, CtImageType Type);
	GDI_IMAGE_ID getImageID();
	bool setDrawable(const GDI_HANDLER DrawableID);
	GDI_HANDLER getDrawable();
	bool setStringID(const GDI_STRING_ID, const CtFontSet& FontSet);
	bool setStringID(const GDI_STRING_ID);
	bool setText(const char *ucStr);
	bool setText(const char *ucStr, const CtFontSet& FontSet);
	bool setText(const unsigned short *ucStr);
	bool setText(const unsigned short *ucStr, const CtFontSet& FontSet);
	unsigned short* getText();

	bool setButtonStyleChange();
	bool setButtonColors(const CtColor& Base, const CtColor& Stroke, const CtColor& Label, const CtColor& LabelStroke = CtColor::NoColor);
	bool setFocusedButtonColors(const CtColor& Base, const CtColor& Stroke, const CtColor& Label, const CtColor& LabelStroke = CtColor::NoColor);
	bool setPressedButtonColors(const CtColor& Base, const CtColor& Stroke, const CtColor& Label, const CtColor& LabelStroke = CtColor::NoColor);
	bool setInvalidButtonColors(const CtColor& Base, const CtColor& Stroke, const CtColor& Label, const CtColor& LabelStroke = CtColor::NoColor);
	
	bool setRepeatTime(unsigned long timRepeat);
	bool setLongPressTime(unsigned long timlong);
	bool setTimLvThresholdTime(unsigned long timLvThreshold);
	bool resetRepeatTime();
	bool resetLongPressTime();
	bool resetTimLvThresholdTime();
protected:
	void ctor(const CtSize& Size, CtButton::Shape Shape);
	
	virtual bool setLayout(int Screen = 0);

	CtWidget* getTop();
	bool setTopColor(const CtColor& fillColor);
	bool setTopColor(const CtColor& fillColor, const CtColor& strokeColor);
	bool setBaseColor(const CtColor& fillColor);
	bool setBaseColor(const CtColor& fillColor, const CtColor& strokeColor);
	bool setState(State _state);
	CtButton::State getState() const; 
	
	virtual bool onPress(const CtEventButton::PressType Type, const CtEventButton::ButtonTimerLevel TimLv = CtEventButton::Level_Default);
	virtual bool onRelease();

	virtual void setProperty();

	virtual bool styleNormal();
	virtual bool styleFocused();
	virtual bool stylePressed();
	virtual bool styleInvalid();

	virtual bool setColors(const CtColor& Base, const CtColor& Stroke, const CtColor& Label, const CtColor& LabelStroke = CtColor::NoColor);
	virtual bool setStroke(short Width);
	
	State			m_State;
	
    unsigned long 	m_LongPressTime;
    unsigned long 	m_RepeatTime;
    unsigned long 	m_IntervalCount;
	unsigned long 	m_TimLvThreshold;

	CtButton::Shape	m_Shape;
    bool 			m_bFocusable;
	int				m_DialIndex;

#if 0	
	CtWidget*		m_pTop;
	CtSize			m_TopSize;
	CtMargin		m_TopMargin;
	CtAlign			m_TopAlign;
#endif
	bool sendPressEvent(CtEventButton::PressType Type, const CtEventButton::ButtonTimerLevel TimLv = CtEventButton::Level_Default);
	bool sendStateEvent(CtEventButton::ChangeState State);
	
	static const unsigned long LongPressTime_Default;
	static const unsigned long RepeatTime_Default;
	
	short			BaseStrokeWidth;
	short			BaseArcWidth;
	
	CtColor 		BaseColor;
	CtColor 		StrokeColor;
	CtColor 		LabelColor;

	CtColor 		FocusedBaseColor;
	CtColor 		FocusedStrokeColor;
	CtColor 		FocusedLabelColor;
	
	CtColor 		PressedBaseColor;
	CtColor 		PressedStrokeColor;
	CtColor 		PressedLabelColor;

	CtColor 		InvalidLabelColor;
	CtColor 		InvalidStrokeColor;
	CtColor 		InvalidBaseColor;

	CtEventButton::ButtonTimerLevel m_TimLv;
private:
	virtual bool setLine(const CtLine& Line);
	virtual bool setLine(CtLineStyle Style, short lineWidth, const CtColor& lineColor);
	virtual bool setFill(const CtFill& Fill);
	virtual bool setRect(const CtRect& Rect);
	virtual bool setRect(const CtColor& fillColor, short edgeWidth, const CtColor& edgeColor = CtColor::NoColor);
	virtual bool setRoundRect(const CtRoundRect& RoundRect);
	virtual bool setRoundRect(short ArcWidth, short ArcHeight, const CtColor& fillColor, short edgeWidth, const CtColor& edgeColor = CtColor::NoColor);
	virtual bool setEllipse(const CtEllipse& Ellipse);
	virtual bool setEllipse(const CtColor& fillColor, short edgeWidth, const CtColor& edgeColor = CtColor::NoColor);
};

inline CtButton::State CtButton::getState() const
{
	return m_State;
}

inline bool CtButton::setFocusable(bool bFocusable)
{
	if (m_bFocusable != bFocusable) {
		m_bFocusable = bFocusable;
		return true;
	}
	return false;
}

inline bool CtButton::isFocusable() const
{
	if (isInvalid() == true)
		return false;
	
	return m_bFocusable;
}

inline bool CtButton::isButton() const
{
	return true;
}

inline int CtButton::getDialIndex() const
{
	return m_DialIndex;
}

#endif
