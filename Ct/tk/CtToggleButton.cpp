/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Rhapsody Version: 7.5.1
 *  Element:          CtButton
 */

#include "CtToggleButton.h"
#include "CtWindow.h"
#include "CtStyle.h"


void CtToggleButton::ctor()
{
	m_bSelect = false;
	m_bHold = false;
	m_bAutoSelect = true;
	setSelectParts(Label);
}

CtToggleButton::CtToggleButton()
{
	ctor();
}

CtToggleButton::CtToggleButton(CtButton::Shape Shape) :
	CtButton(Shape)
{
	ctor();
}

CtToggleButton::CtToggleButton(const CtSize& Size, CtButton::Shape Shape) :
	CtButton(Size, Shape)
{
	ctor();
}

CtToggleButton::CtToggleButton(const CtSize& Size, CtSelectParts SelectParts, CtButton::Shape Shape) :
	CtButton(Size, Shape)
{
	ctor();
	setSelectParts(SelectParts);
}

CtToggleButton::CtToggleButton(const CtRegion& Region, CtButton::Shape Shape) :
	CtButton(Region, Shape)
{
	ctor();
}


CtToggleButton::CtToggleButton(const GDI_IMAGE_ID ImageID, CtButton::Shape Shape) :
	CtButton(ImageID, Shape)
{
	ctor();
}

CtToggleButton::CtToggleButton(const GDI_HANDLER DrawableID, CtButton::Shape Shape) :
	CtButton(DrawableID, Shape)
{
	ctor();
}

CtToggleButton::CtToggleButton(const GDI_STRING_ID StringID, const CtFontSet& FontSet, CtButton::Shape Shape) :
	CtButton(StringID, FontSet, Shape)
{
	ctor();
}

CtToggleButton::CtToggleButton(const GDI_STRING_ID StringID, CtButton::Shape Shape) :
	CtButton(StringID, Shape)
{
	ctor();
}

CtToggleButton::CtToggleButton(const char* ucStr, const CtFontSet& FontSet, CtButton::Shape Shape) :
	CtButton(ucStr, FontSet, Shape)
{
	ctor();
}

CtToggleButton::CtToggleButton(const char* ucStr, CtButton::Shape Shape) :
	CtButton(ucStr, Shape)
{
	ctor();
}

CtToggleButton::CtToggleButton(const unsigned short* ucStr, const CtFontSet& FontSet, CtButton::Shape Shape) :
	CtButton(ucStr, FontSet, Shape)
{
	ctor();
}

CtToggleButton::CtToggleButton(const unsigned short* ucStr, CtButton::Shape Shape) :
	CtButton(ucStr, Shape)
{
	ctor();
}

CtToggleButton::CtToggleButton(CtLabel *pLabel, CtButton::Shape Shape) :
	CtButton(pLabel, Shape)
{
	ctor();
}

CtToggleButton::CtToggleButton(CtLayout *pLayout, CtButton::Shape Shape) :
	CtButton(pLayout, Shape)
{
	ctor();
}

	
CtToggleButton::CtToggleButton(const CtSize& Size, const GDI_IMAGE_ID ImageID, CtButton::Shape Shape) :
	CtButton(Size, ImageID, Shape)
{
	ctor();
}

CtToggleButton::CtToggleButton(const CtSize& Size, const GDI_HANDLER DrawableID, CtButton::Shape Shape) :
	CtButton(Size, DrawableID, Shape)
{
	ctor();
}

CtToggleButton::CtToggleButton(const CtSize& Size, const GDI_STRING_ID StringID, const CtFontSet& FontSet, CtButton::Shape Shape) :
	CtButton(Size, StringID, FontSet, Shape)
{
	ctor();
}

CtToggleButton::CtToggleButton(const CtSize& Size, const GDI_STRING_ID StringID, CtButton::Shape Shape) :
	CtButton(Size, StringID, Shape)
{
	ctor();
}

CtToggleButton::CtToggleButton(const CtSize& Size, const char* ucStr, const CtFontSet& FontSet, CtButton::Shape Shape) :
	CtButton(Size, ucStr, FontSet, Shape)
{
	ctor();
}

CtToggleButton::CtToggleButton(const CtSize& Size, const char* ucStr, CtButton::Shape Shape) :
	CtButton(Size, ucStr, Shape)
{
	ctor();
}

CtToggleButton::CtToggleButton(const CtSize& Size, const unsigned short* ucStr, const CtFontSet& FontSet, CtButton::Shape Shape) :
	CtButton(Size, ucStr, FontSet, Shape)
{
	ctor();
}

CtToggleButton::CtToggleButton(const CtSize& Size, const unsigned short* ucStr, CtButton::Shape Shape) :
	CtButton(Size, ucStr, Shape)
{
	ctor();
}

CtToggleButton::CtToggleButton(const CtSize& Size, CtLabel *pLabel, CtButton::Shape Shape) :
	CtButton(Size, pLabel, Shape)
{
	ctor();
}

CtToggleButton::CtToggleButton(const CtSize& Size, CtLayout *pLayout, CtButton::Shape Shape) :
	CtButton(Size, pLayout, Shape)
{
	ctor();
}

bool CtToggleButton::onRelease()
{
	return CtButton::onRelease();
}

bool CtToggleButton::isSelected()
{
	return m_bSelect;
}

void CtToggleButton::setSelect(bool bSelect)
{
	bool bRet = false;
	
	if (m_bSelect == bSelect) {
		return;
	}
	
	m_bSelect = bSelect;

	if (m_bSelect == true) {
		//CtDebugPrint(CtDbg, "send select:%p\n", this);
		sendStateEvent(CtEventButton::Select);
	}

	switch (m_State) {
	case StateNormal:
	case StateSilentFocused:
		bRet = styleNormal();
		break;
	case StateFocused:
	case StatePressed:
		bRet = styleFocused();
		break;
	case StateInvalid:
		bRet = styleInvalid();
		break;
	default:
		break;
	}
	if ((bRet == true) && (isVisible() == true)) {
		setInvalidate();
	}
}

bool CtToggleButton::onPress(const CtEventButton::PressType Type, const CtEventButton::ButtonTimerLevel TimLv) {
	bool bSelect;

	if (m_bHold == true) {
		bSelect = true;
	}
	else {
		bSelect = (m_bSelect == true) ? false : true;
	}

 	if (Type == CtEventButton::ShortPress || Type == CtEventButton::Release) {
		if(m_bAutoSelect) setSelect(bSelect);
	}

	return CtButton::onPress(Type);

}

bool CtToggleButton::styleNormal()
{

	bool bRet = false;

	if (m_pDrawInfo == NULL)
		return bRet;

	if (m_bSelect == true) {
		if (setBaseColor(SelectBaseColor, SelectStrokeColor) == true)
			bRet = true;
		if (setTopColor(SelectLabelColor) == true)
			bRet = true;
	}
	else {
		if (CtButton::styleNormal() == true)
			bRet = true;
	}

	return bRet;

}
bool CtToggleButton::styleFocused() {
	bool bRet = false;

	if (m_pDrawInfo == NULL)
		return bRet;
	const CtStyle::CtProperty& prop = CtStyle::getProperty();

	if (m_bSelect == true) {
		if (setBaseColor(SelectFocusedBaseColor, SelectFocusedStrokeColor) == true)
			bRet = true;
		if (setTopColor(SelectFocusedLabelColor) == true)
			bRet = true;
	}
	else {
		if (CtButton::styleFocused() == true)
			bRet = true;
	}
	return bRet;

}

void CtToggleButton::setSelectParts(CtSelectParts selectParts) { 
	m_SelectParts = selectParts;

	const CtStyle::CtProperty& prop = CtStyle::getProperty();
	if (selectParts == Stroke) {
		// SelectéûÇÃColorê›íË
		SelectBaseColor = prop.Button.Normal.Base;
		SelectStrokeColor = CtColor::orange;
		SelectLabelColor = prop.Button.Normal.Label;

		SelectFocusedBaseColor = prop.Button.Selected.Base;
		SelectFocusedStrokeColor = CtColor::orange;
		SelectFocusedLabelColor = prop.Button.Selected.Label;

		// SelectèÛë‘Ç≈Ç»Ç¢Ç∆Ç´ÇÃColorê›íË
		setButtonColors(prop.Button.Normal.Base, prop.Button.Normal.Stroke, prop.Button.Normal.Label);
		setFocusedButtonColors(prop.Button.Selected.Base, prop.Button.Normal.Stroke, prop.Button.Selected.Label);
		setPressedButtonColors(prop.Button.Selected.Base, prop.Button.Normal.Stroke, prop.Button.Selected.Label);
	}
	else if (selectParts == Label) {
		// SelectéûÇÃColorê›íË
		SelectBaseColor = prop.Button.Selected.Base;
		SelectStrokeColor = prop.Button.Normal.Stroke;
		SelectLabelColor = prop.Button.Selected.Label;

		SelectFocusedBaseColor = prop.Button.Selected.Base;
		SelectFocusedStrokeColor = CtColor::orange;
		SelectFocusedLabelColor = prop.Button.Selected.Label;

		// SelectèÛë‘Ç≈Ç»Ç¢Ç∆Ç´ÇÃColorê›íË
		setButtonColors(prop.Button.Normal.Base, prop.Button.Normal.Stroke, prop.Button.Normal.Label);
		setFocusedButtonColors(prop.Button.Normal.Base, prop.Button.Selected.Stroke, prop.Button.Normal.Label);
		setPressedButtonColors(prop.Button.Normal.Base, prop.Button.Selected.Stroke, prop.Button.Normal.Label);
	}
}
