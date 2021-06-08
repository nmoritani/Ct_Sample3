/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:	CtButton
 */


#ifndef __CtToggleButton_H__
#define __CtToggleButton_H__

#include "Ct.h"
#include "CtButton.h"

class CtToggleButton : public CtButton {
public:
	// SelectèÛë‘éûÇ…ïœçXÇ∑ÇÈïîïiÇéwíËÇ∑ÇÈ
	enum CtSelectParts {
		Stroke,
		Label
	};

	CtToggleButton();
	CtToggleButton(CtButton::Shape Shape);
	CtToggleButton(const CtSize& Size, CtButton::Shape Shape = RoundRect);
	CtToggleButton(const CtSize& Size, CtSelectParts SelectParts, CtButton::Shape Shape = RoundRect);
	CtToggleButton(const CtRegion& Region, CtButton::Shape Shape = RoundRect);

	CtToggleButton(const GDI_IMAGE_ID ImageID, CtButton::Shape Shape = RoundRect);
	CtToggleButton(const GDI_HANDLER DrawableID, CtButton::Shape Shape = RoundRect);
	CtToggleButton(const GDI_STRING_ID StringID, const CtFontSet& FontSet, CtButton::Shape Shape = RoundRect);
	CtToggleButton(const GDI_STRING_ID StringID, CtButton::Shape Shape = RoundRect);
	CtToggleButton(const char* ucStr, const CtFontSet& FontSet, CtButton::Shape Shape = RoundRect);
	CtToggleButton(const char* ucStr, CtButton::Shape Shape = RoundRect);
	CtToggleButton(const unsigned short* ucStr, const CtFontSet& FontSet, CtButton::Shape Shape = RoundRect);
	CtToggleButton(const unsigned short* ucStr, CtButton::Shape Shape = RoundRect);
	CtToggleButton(CtLabel *pLabel, CtButton::Shape Shape = RoundRect);
	CtToggleButton(CtLayout *pLayout, CtButton::Shape Shape = RoundRect);

	CtToggleButton(const CtSize& Size, const GDI_IMAGE_ID ImageID, CtButton::Shape Shape = RoundRect);
	CtToggleButton(const CtSize& Size, const GDI_HANDLER DrawableID, CtButton::Shape Shape = RoundRect);
	CtToggleButton(const CtSize& Size, const GDI_STRING_ID StringID, const CtFontSet& FontSet, CtButton::Shape Shape = RoundRect);
	CtToggleButton(const CtSize& Size, const GDI_STRING_ID StringID, CtButton::Shape Shape = RoundRect);
	CtToggleButton(const CtSize& Size, const char* ucStr, const CtFontSet& FontSet, CtButton::Shape Shape = RoundRect);
	CtToggleButton(const CtSize& Size, const char* ucStr, CtButton::Shape Shape = RoundRect);
	CtToggleButton(const CtSize& Size, const unsigned short* ucStr, const CtFontSet& FontSet, CtButton::Shape Shape = RoundRect);
	CtToggleButton(const CtSize& Size, const unsigned short* ucStr, CtButton::Shape Shape = RoundRect);
	CtToggleButton(const CtSize& Size, CtLabel *pLabel, CtButton::Shape Shape = RoundRect);
	CtToggleButton(const CtSize& Size, CtLayout *pLayout, CtButton::Shape Shape = RoundRect);

	virtual bool setAutoSelectMode(bool bAutoSelect) { m_bAutoSelect = bAutoSelect; return true; };
	virtual void setSelect(bool bSelect);
	virtual void setSelectParts(CtSelectParts selectParts = Label);
	virtual bool isSelected();
	virtual void setHold(bool bHold) { m_bHold = bHold; }

protected:
	void ctor();
	virtual bool onPress(const CtEventButton::PressType Type, const CtEventButton::ButtonTimerLevel TimLv = CtEventButton::Level_Default);
	virtual bool onRelease();

	virtual bool styleNormal();
	virtual bool styleFocused();

private:
	bool m_bSelect;
	bool m_bHold;
	bool m_bAutoSelect;

	CtColor 		SelectBaseColor;
	CtColor 		SelectStrokeColor;
	CtColor 		SelectLabelColor;

	CtColor 		SelectFocusedBaseColor;
	CtColor 		SelectFocusedStrokeColor;
	CtColor 		SelectFocusedLabelColor;


	CtSelectParts  m_SelectParts;
};

#endif
