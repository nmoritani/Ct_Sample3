/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:	CtLinkButton
 */


#ifndef __CtLinkButton_H__
#define __CtLinkButton_H__

#include "Ct.h"
#include "CtButton.h"
#include "CtWindow.h"
#include "CtWindowContents.h"

class CtLinkButton : public CtButton {
public :
	CtLinkButton();

	CtLinkButton(CtWindowID WindowID, CtOpenType Type, CtButton::Shape Shape = RoundRect);
	CtLinkButton(CtWindowID WindowID, CtOpenType Type, CtLabel *pLabel, CtButton::Shape Shape = RoundRect);
	CtLinkButton(CtWindowID WindowID, CtOpenType Type, CtLayout *pLayout, CtButton::Shape Shape = RoundRect);
	CtLinkButton(CtWindowID WindowID, CtOpenType Type, const CtRegion& Region, CtButton::Shape Shape = RoundRect);
	CtLinkButton(CtWindowID WindowID, CtOpenType Type, const GDI_IMAGE_ID ImageID, CtButton::Shape Shape = RoundRect);
	CtLinkButton(CtWindowID WindowID, CtOpenType Type, const GDI_STRING_ID StringID, CtButton::Shape Shape = RoundRect);
	CtLinkButton(CtWindowID WindowID, CtOpenType Type, const char *ucStr, CtButton::Shape Shape = RoundRect);

	CtLinkButton(CtWindowID WindowID, CtOpenType Type, const GDI_STRING_ID StringID, const CtFontSet& FontSet, CtButton::Shape Shape = RoundRect);
	CtLinkButton(CtWindowID WindowID, CtOpenType Type, const char *ucStr, const CtFontSet& FontSet, CtButton::Shape Shape = RoundRect);

	CtLinkButton(CtWindowID WindowID, CtOpenType Type, const CtSize& Size, CtButton::Shape Shape = RoundRect);
	CtLinkButton(CtWindowID WindowID, CtOpenType Type, const CtSize& Size, CtLabel *pLabel, CtButton::Shape Shape = RoundRect);
	CtLinkButton(CtWindowID WindowID, CtOpenType Type, const CtSize& Size, CtLayout *pLayout, CtButton::Shape Shape = RoundRect);
	CtLinkButton(CtWindowID WindowID, CtOpenType Type, const CtSize& Size, const GDI_IMAGE_ID ImageID, CtButton::Shape Shape = RoundRect);
	CtLinkButton(CtWindowID WindowID, CtOpenType Type, const CtSize& Size, const GDI_STRING_ID StringID, CtButton::Shape Shape = RoundRect);
	CtLinkButton(CtWindowID WindowID, CtOpenType Type, const CtSize& Size, const char *ucStr, CtButton::Shape Shape = RoundRect);

	CtLinkButton(CtWindowID WindowID, CtOpenType Type, const CtSize& Size, const GDI_STRING_ID StringID, const CtFontSet& FontSet, CtButton::Shape Shape = RoundRect);
	CtLinkButton(CtWindowID WindowID, CtOpenType Type, const CtSize& Size, const char *ucStr, const CtFontSet& FontSet, CtButton::Shape Shape = RoundRect);

	inline void setOpenWindow(const CtWindowID WindowID, const CtOpenType OpenType, CtWindowContents *pContents);
	inline void setContents(CtWindowContents *pContents);
	inline void setScreen(CtScreenSel ScreenSel);

protected:
	//	bool onPress(const CtEventButton::PressType Type);
	bool onRelease();
	
private:
	CtScreenSel m_ScreenSel;
	CtWindowID	m_WindowID;
	CtOpenType	m_OpenType;
	CtWindowContents *m_pContents;
};

inline void CtLinkButton::setContents(CtWindowContents *pContents)
{
	m_pContents = pContents;
}

inline void CtLinkButton::setScreen(CtScreenSel ScreenSel)
{
	m_ScreenSel = ScreenSel;
}

inline void CtLinkButton::setOpenWindow(const CtWindowID WindowID, const CtOpenType OpenType, CtWindowContents *pContents)
{
	m_WindowID = WindowID;
	m_OpenType = OpenType;
	m_pContents = pContents;
}

#endif
