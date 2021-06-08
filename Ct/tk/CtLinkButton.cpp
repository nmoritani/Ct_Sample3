/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:          CtLinkButton
 */

#include "CtLinkButton.h"
#include "CtWindow.h"

CtLinkButton::CtLinkButton() :
	m_ScreenSel((CtScreenSel)(ScreenLCD|ScreenLOUT)),
	m_WindowID(WindowNone),
	m_OpenType(Close),
	m_pContents(NULL),
	CtButton(RoundRect)
{
}

CtLinkButton::CtLinkButton(CtWindowID WindowID, CtOpenType Type, CtButton::Shape Shape) :
	m_ScreenSel((CtScreenSel)(ScreenLCD|ScreenLOUT)),
	m_WindowID(WindowID),
	m_OpenType(Type),
	m_pContents(NULL),
	CtButton(Shape)
{
}

CtLinkButton::CtLinkButton(CtWindowID WindowID, CtOpenType Type, const CtSize& Size, CtButton::Shape Shape) :
	m_ScreenSel((CtScreenSel)(ScreenLCD|ScreenLOUT)),
	m_WindowID(WindowID),
	m_OpenType(Type),
	m_pContents(NULL),
	CtButton(Size, Shape)
{
}

CtLinkButton::CtLinkButton(CtWindowID WindowID, CtOpenType Type, const CtRegion& Region, CtButton::Shape Shape) :
	m_ScreenSel((CtScreenSel)(ScreenLCD|ScreenLOUT)),
	m_WindowID(WindowID),
	m_OpenType(Type),
	m_pContents(NULL),
	CtButton(Region, Shape)
{
}

CtLinkButton::CtLinkButton(CtWindowID WindowID, CtOpenType Type, const char *ucStr, const CtFontSet& FontSet, CtButton::Shape Shape) :
	m_ScreenSel((CtScreenSel)(ScreenLCD|ScreenLOUT)),
	m_WindowID(WindowID),
	m_OpenType(Type),
	m_pContents(NULL),
	CtButton(ucStr, FontSet, Shape)
{
}

CtLinkButton::CtLinkButton(CtWindowID WindowID, CtOpenType Type, const GDI_STRING_ID StringID, const CtFontSet& FontSet, CtButton::Shape Shape) :
	m_ScreenSel((CtScreenSel)(ScreenLCD|ScreenLOUT)),
	m_WindowID(WindowID),
	m_OpenType(Type),
	m_pContents(NULL),
	CtButton(StringID, FontSet, Shape)
{
}

CtLinkButton::CtLinkButton(CtWindowID WindowID, CtOpenType Type, const char * ucStr, CtButton::Shape Shape) :
	m_ScreenSel((CtScreenSel)(ScreenLCD | ScreenLOUT)),
	m_WindowID(WindowID),
	m_OpenType(Type),
	m_pContents(NULL),
	CtButton(ucStr, Shape)
{
}

CtLinkButton::CtLinkButton(CtWindowID WindowID, CtOpenType Type, const GDI_STRING_ID StringID, CtButton::Shape Shape) :
	m_ScreenSel((CtScreenSel)(ScreenLCD | ScreenLOUT)),
	m_WindowID(WindowID),
	m_OpenType(Type),
	m_pContents(NULL),
	CtButton(StringID, Shape)
{
}

CtLinkButton::CtLinkButton(CtWindowID WindowID, CtOpenType Type, const GDI_IMAGE_ID ImageID, CtButton::Shape Shape) :
	m_ScreenSel((CtScreenSel)(ScreenLCD|ScreenLOUT)),
	m_WindowID(WindowID),
	m_OpenType(Type),
	m_pContents(NULL),
	CtButton(ImageID, Shape)
{
}

CtLinkButton::CtLinkButton(CtWindowID WindowID, CtOpenType Type, CtLabel * pLabel, CtButton::Shape Shape) :
	m_ScreenSel((CtScreenSel)(ScreenLCD | ScreenLOUT)),
	m_WindowID(WindowID),
	m_OpenType(Type),
	m_pContents(NULL),
	CtButton(pLabel, Shape)
{
}

CtLinkButton::CtLinkButton(CtWindowID WindowID, CtOpenType Type, CtLayout * pLayout, CtButton::Shape Shape) :
	m_ScreenSel((CtScreenSel)(ScreenLCD | ScreenLOUT)),
	m_WindowID(WindowID),
	m_OpenType(Type),
	m_pContents(NULL),
	CtButton(pLayout, Shape)
{
}

CtLinkButton::CtLinkButton(CtWindowID WindowID, CtOpenType Type, const CtSize& Size, const char *ucStr, const CtFontSet& FontSet, CtButton::Shape Shape) :
	m_ScreenSel((CtScreenSel)(ScreenLCD|ScreenLOUT)),
	m_WindowID(WindowID),
	m_OpenType(Type),
	m_pContents(NULL),
	CtButton(Size, ucStr, FontSet, Shape)
{
}

CtLinkButton::CtLinkButton(CtWindowID WindowID, CtOpenType Type, const CtSize& Size, const GDI_STRING_ID StringID, const CtFontSet& FontSet, CtButton::Shape Shape) :
	m_ScreenSel((CtScreenSel)(ScreenLCD|ScreenLOUT)),
	m_WindowID(WindowID),
	m_OpenType(Type),
	m_pContents(NULL),
	CtButton(Size, StringID, FontSet, Shape)
{
}

CtLinkButton::CtLinkButton(CtWindowID WindowID, CtOpenType Type, const CtSize & Size, const char * ucStr, CtButton::Shape Shape) :
	m_ScreenSel((CtScreenSel)(ScreenLCD | ScreenLOUT)),
	m_WindowID(WindowID),
	m_OpenType(Type),
	m_pContents(NULL),
	CtButton(Size, ucStr, Shape)
{
}

CtLinkButton::CtLinkButton(CtWindowID WindowID, CtOpenType Type, const CtSize & Size, const GDI_STRING_ID StringID, CtButton::Shape Shape) :
	m_ScreenSel((CtScreenSel)(ScreenLCD | ScreenLOUT)),
	m_WindowID(WindowID),
	m_OpenType(Type),
	m_pContents(NULL),
	CtButton(Size, StringID, Shape)
{
}

CtLinkButton::CtLinkButton(CtWindowID WindowID, CtOpenType Type, const CtSize& Size, const GDI_IMAGE_ID ImageID, CtButton::Shape Shape) :
	m_ScreenSel((CtScreenSel)(ScreenLCD|ScreenLOUT)),
	m_WindowID(WindowID),
	m_OpenType(Type),
	m_pContents(NULL),
	CtButton(Size, ImageID, Shape)
{
}

CtLinkButton::CtLinkButton(CtWindowID WindowID, CtOpenType Type, const CtSize & Size, CtLabel * pLabel, CtButton::Shape Shape) :
	m_ScreenSel((CtScreenSel)(ScreenLCD | ScreenLOUT)),
	m_WindowID(WindowID),
	m_OpenType(Type),
	m_pContents(NULL),
	CtButton(Size, pLabel, Shape)
{
}

CtLinkButton::CtLinkButton(CtWindowID WindowID, CtOpenType Type, const CtSize & Size, CtLayout * pLayout, CtButton::Shape Shape) :
	m_ScreenSel((CtScreenSel)(ScreenLCD | ScreenLOUT)),
	m_WindowID(WindowID),
	m_OpenType(Type),
	m_pContents(NULL),
	CtButton(Size, pLayout, Shape)
{
}


bool CtLinkButton::onRelease()
{
	bool bRet = false;
	bRet = CtButton::onRelease();
	
	CtWindow *pWindow = NULL;
	if ((pWindow = getWindow()) != NULL) {
#if 0 /*@salvage*/
		pWindow->requestWindow(m_WindowID, m_OpenType, m_pContents);
#endif
	}
	return bRet;
}
