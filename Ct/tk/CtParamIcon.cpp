/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:          CtParamIcon
 */

#include "CtParamIcon.h"
#include "AplParamService.h"
#include "CtStyle.h"
#define APL_PARAM_INVALID 0xCBCBCBCB

void CtParamIcon::ctor()
{
	setClassType(CtClassType_ParamIcon);
	setEventFilter(EventParam);
	
	m_ParamId = APL_PARAM_INVALID;
	m_ParamData = APL_PARAM_INVALID;
}

CtParamIcon::CtParamIcon()
{
	ctor();
}

CtParamIcon::CtParamIcon(const CtSize& Size) :
	CtLabel(Size)
{
	ctor();
}

CtParamIcon::CtParamIcon(const CtColor& Color) :
	CtLabel(Color)
{
	ctor();
}

CtParamIcon::CtParamIcon(const GDI_IMAGE_ID ImageID) :
	CtLabel(ImageID)
{
	ctor();
}

CtParamIcon::CtParamIcon(const GDI_IMAGE_ID ImageID, const CtColor& fillColor, const CtColor& edgeColor) :
	CtLabel(ImageID, fillColor, edgeColor)
{
	ctor();
}

CtParamIcon::CtParamIcon(const GDI_HANDLER DrawableID) :
	CtLabel(DrawableID)
{
	ctor();
}

CtParamIcon::CtParamIcon(const GDI_STRING_ID StringID, const CtFontSet& FontSet) :
	CtLabel(StringID, FontSet)
{
	ctor();
}

CtParamIcon::CtParamIcon(const GDI_STRING_ID StringID) :
	CtLabel(StringID)
{
	ctor();
}

CtParamIcon::CtParamIcon(const char* pStr, const CtFontSet& FontSet) :
	CtLabel(pStr, FontSet)
{
	ctor();
}

CtParamIcon::CtParamIcon(const char* pStr) :
	CtLabel(pStr)
{
	ctor();
}

CtParamIcon::CtParamIcon(const unsigned short* pStr, const CtFontSet& FontSet) :
	CtLabel(pStr, FontSet)
{
	ctor();
}

CtParamIcon::CtParamIcon(const unsigned short* pStr) :
	CtLabel(pStr)
{
	ctor();
}
	
CtParamIcon::CtParamIcon(const CtLine& Line) :
	CtLabel(Line)
{
	ctor();
}

CtParamIcon::CtParamIcon(const CtRect& Rect) :
	CtLabel(Rect)
{
	ctor();
}

CtParamIcon::CtParamIcon(const CtFill& Fill) :
	CtLabel(Fill)
{
	ctor();
}

CtParamIcon::CtParamIcon(const CtRoundRect& RoundRect) :
	CtLabel(RoundRect)
{
	ctor();
}

CtParamIcon::CtParamIcon(const CtEllipse& Ellipse) :
	CtLabel(Ellipse)
{
	ctor();
}

CtParamIcon::CtParamIcon(short Width, short Height, short BufWidth, short BufHeight, const unsigned char* Data, CtImageType Type) :
	CtLabel(Width, Height, BufWidth, BufHeight, Data, Type)
{
	ctor();
}

CtParamIcon::CtParamIcon(short Width, short Height, short YPlaneSize, short PlaneStride, short PlaneHeight, const unsigned char* pYPlane, const unsigned char* pCPlane, CtImageType Type) :
	CtLabel(Width, Height, YPlaneSize, PlaneStride, PlaneHeight, pYPlane, pCPlane, Type)
{
	ctor();
}
	
CtParamIcon::CtParamIcon(const CtSize& Size, const CtColor& Color) :
	CtLabel(Size, Color)
{
	ctor();
}

CtParamIcon::CtParamIcon(const CtSize& Size, const GDI_IMAGE_ID ImageID) :
	CtLabel(Size, ImageID)
{
	ctor();
}

CtParamIcon::CtParamIcon(const CtSize& Size, const GDI_IMAGE_ID ImageID, const CtColor& fillColor, const CtColor& edgeColor) :
	CtLabel(Size, ImageID, fillColor, edgeColor)
{
	ctor();
}

CtParamIcon::CtParamIcon(const CtSize& Size, const GDI_HANDLER DrawableID) :
	CtLabel(Size, DrawableID)
{
	ctor();
}

CtParamIcon::CtParamIcon(const CtSize& Size, const GDI_STRING_ID StringID, const CtFontSet& FontSet) :
	CtLabel(Size, StringID, FontSet)
{
	ctor();
}

CtParamIcon::CtParamIcon(const CtSize& Size, const GDI_STRING_ID StringID) :
	CtLabel(Size, StringID)
{
	ctor();
}

CtParamIcon::CtParamIcon(const CtSize& Size, const char* pStr, const CtFontSet& FontSet) :
	CtLabel(Size, pStr, FontSet)
{
	ctor();
}

CtParamIcon::CtParamIcon(const CtSize& Size, const char* pStr) :
	CtLabel(Size, pStr)
{
	ctor();
}

CtParamIcon::CtParamIcon(const CtSize& Size, const unsigned short* pStr, const CtFontSet& FontSet) :
	CtLabel(Size, pStr, FontSet)
{
	ctor();
}

CtParamIcon::CtParamIcon(const CtSize& Size, const unsigned short* pStr) :
	CtLabel(Size, pStr)
{
	ctor();
}

CtParamIcon::CtParamIcon(const CtSize& Size, const CtLine& Line) :
	CtLabel(Size, Line)
{
	ctor();
}

CtParamIcon::CtParamIcon(const CtSize& Size, const CtRect& Rect) :
	CtLabel(Size, Rect)
{
	ctor();
}

CtParamIcon::CtParamIcon(const CtSize& Size, const CtRoundRect& RoundRect) :
	CtLabel(Size, RoundRect)
{
	ctor();
}

CtParamIcon::CtParamIcon(const CtSize& Size, const CtEllipse& Ellipse) :
	CtLabel(Size, Ellipse)
{
	ctor();
}

CtParamIcon::CtParamIcon(const CtSize& Size, short Width, short Height, short BufWidth, short BufHeight, const unsigned char* Data, CtImageType Type) :
	CtLabel(Size, Width, Height, BufWidth, BufHeight, Data, Type)
{
	ctor();
}

CtParamIcon::CtParamIcon(const CtSize& Size, short Width, short Height, short YPlaneSize, short PlaneStride, short PlaneHeight, const unsigned char* pYPlane, const unsigned char* pCPlane, CtImageType Type) :
	CtLabel(Size, Width, Height, YPlaneSize, PlaneStride, PlaneHeight, pYPlane, pCPlane, Type)
{
	ctor();
}
	

CtParamIcon::~CtParamIcon()
{
}


bool CtParamIcon::setParam(int ParamID, int ParamData)
{
	bool bRet = false;
	
	if (m_ParamId != ParamID) {
		m_ParamId = ParamID;
		bRet = true;
	}

	if (m_ParamData != ParamData) {
		m_ParamData = ParamData;
		bRet = true;
	}

	return bRet;
}

bool CtParamIcon::handleParamEvent(const CtEventParam& Param)
{
	if (Param.getParamId() == m_ParamId) {
		setInvalidate();
		return true;
	}
	return false;
}

CtDrawInfo* CtParamIcon::getDrawInfo(const CtRegion& Clip, int Screen)
{
	if (m_ParamData == APL_PARAM_GET_DATA(m_ParamId))
		return CtLabel::getDrawInfo(Clip, Screen);

	return NULL;
}

