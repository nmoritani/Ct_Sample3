/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:          CtLabel
 */

#include "CtLabel.h"
#include "CtStyle.h"

void CtLabel::ctor()
{
	setClassType(CtClassType_Label);
	
	m_bFastDraw = false;
	m_pDrawInfo = NULL;
	m_fillColor = CtColor::NoColor;
	m_edgeColor = CtColor::NoColor;
	m_bFixedColor = false;

	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		m_ClearRegion[i] = NoRegion;
	}
}

CtLabel::CtLabel()
{
	ctor();
}

CtLabel::CtLabel(const CtSize& Size) :
	CtWidget(Size)
{
	ctor();
}

CtLabel::CtLabel(const CtRegion& Region) :
	CtWidget(Region)
{
	ctor();
}
#if 0
CtLabel::CtLabel(const CtLabel& Label) :
	CtWidget(Label.getSize())
{
	ctor();
	setColor(Label.m_fillColor, Label.m_edgeColor);
}
#endif
CtLabel::CtLabel(const CtColor& Color)
{
	ctor();
	setColor(Color);
}

CtLabel::CtLabel(const GDI_IMAGE_ID ImageID)
{
	ctor();
	setImage(ImageID, CtColor::NoColor, CtColor::NoColor);
}

CtLabel::CtLabel(const GDI_IMAGE_ID ImageID, const CtColor& fillColor, const CtColor& edgeColor)
{
	ctor();
	setImage(ImageID, fillColor, edgeColor);
}

CtLabel::CtLabel(const GDI_HANDLER DrawableID)
{
	ctor();
	setDrawable(DrawableID);
}

CtLabel::CtLabel(const GDI_STRING_ID StringID, const CtFontSet& FontSet)
{
	ctor();
	setStringID(StringID, FontSet);
}

CtLabel::CtLabel(const GDI_STRING_ID StringID)
{
	ctor();
	setStringID(StringID, CtStyle::getProperty().FontSet);
}

CtLabel::CtLabel(const char* pStr, const CtFontSet& FontSet)
{
	ctor();
	setText(pStr, FontSet);
}

CtLabel::CtLabel(const char* pStr)
{
	ctor();
	setText(pStr, CtStyle::getProperty().FontSet);
}

CtLabel::CtLabel(const unsigned short* pStr, const CtFontSet& FontSet)
{
	ctor();
	setText(pStr, FontSet);
}

CtLabel::CtLabel(const unsigned short* pStr)
{
	ctor();
	setText(pStr, CtStyle::getProperty().FontSet);
}
	
CtLabel::CtLabel(const CtLine& Line)
{
	ctor();
	setLine(Line);
}

CtLabel::CtLabel(const CtRect& Rect)
{
	ctor();
	setRect(Rect);
}

CtLabel::CtLabel(const CtFill& Fill)
{
	ctor();
	setFill(Fill);
}

CtLabel::CtLabel(const CtRoundRect& RoundRect)
{
	ctor();
	setRoundRect(RoundRect);
}

CtLabel::CtLabel(const CtEllipse& Ellipse)
{
	ctor();
	setEllipse(Ellipse);
}

CtLabel::CtLabel(short Width, short Height, short BufWidth, short BufHeight, const unsigned char* Data, CtImageType Type)
{
	ctor();
	setImage(Width, Height, BufWidth, BufHeight, Data, Type);
}

CtLabel::CtLabel(short Width, short Height, short YPlaneSize, short PlaneStride, short PlaneHeight, const unsigned char* pYPlane, const unsigned char* pCPlane, CtImageType Type)
{
	ctor();
	setImage(Width, Height, YPlaneSize, PlaneStride, PlaneHeight, pYPlane, pCPlane, Type);
}
	
CtLabel::CtLabel(const CtSize& Size, const CtColor& Color) :
	CtWidget(Size)
{
	ctor();
	setColor(Color);
}

CtLabel::CtLabel(const CtSize& Size, const GDI_IMAGE_ID ImageID) :
	CtWidget(Size)
{
	ctor();
	setImage(ImageID);
}

CtLabel::CtLabel(const CtSize& Size, const GDI_IMAGE_ID ImageID, const CtColor& fillColor, const CtColor& edgeColor) :
	CtWidget(Size)
{
	ctor();
	setImage(ImageID, fillColor, edgeColor);
}

CtLabel::CtLabel(const CtSize& Size, const GDI_HANDLER DrawableID) :
	CtWidget(Size)
{
	ctor();
	setDrawable(DrawableID);
}

CtLabel::CtLabel(const CtSize& Size, const GDI_STRING_ID StringID, const CtFontSet& FontSet) :
	CtWidget(Size)
{
	ctor();
	setStringID(StringID, FontSet);
}

CtLabel::CtLabel(const CtSize& Size, const GDI_STRING_ID StringID) :
	CtWidget(Size)
{
	ctor();
	setStringID(StringID);
}

CtLabel::CtLabel(const CtSize& Size, const char* pStr, const CtFontSet& FontSet) :
	CtWidget(Size)
{
	ctor();
	setText(pStr, FontSet);
}

CtLabel::CtLabel(const CtSize& Size, const char* pStr) :
	CtWidget(Size)
{
	ctor();
	setText(pStr);
}

CtLabel::CtLabel(const CtSize& Size, const unsigned short* pStr, const CtFontSet& FontSet) :
	CtWidget(Size)
{
	ctor();
	setText(pStr, FontSet);
}

CtLabel::CtLabel(const CtSize& Size, const unsigned short* pStr) :
	CtWidget(Size)
{
	ctor();
	setText(pStr);
}

CtLabel::CtLabel(const CtSize& Size, const CtLine& Line) :
	CtWidget(Size)
{
	ctor();
	setLine(Line);
}

CtLabel::CtLabel(const CtSize& Size, const CtRect& Rect) :
	CtWidget(Size)
{
	ctor();
	setRect(Rect);
}

CtLabel::CtLabel(const CtSize& Size, const CtFill& Fill) :
	CtWidget(Size)
{
	ctor();
	setFill(Fill);
}

CtLabel::CtLabel(const CtSize& Size, const CtRoundRect& RoundRect) :
	CtWidget(Size)
{
	ctor();
	setRoundRect(RoundRect);
}

CtLabel::CtLabel(const CtSize& Size, const CtEllipse& Ellipse) :
	CtWidget(Size)
{
	ctor();
	setEllipse(Ellipse);
}

CtLabel::CtLabel(const CtSize& Size, short Width, short Height, short BufWidth, short BufHeight, const unsigned char* Data, CtImageType Type) : 
	CtWidget(Size)
{
	ctor();
	setImage(Width, Height, BufWidth, BufHeight, Data, Type);
}

CtLabel::CtLabel(const CtSize& Size, short Width, short Height, short YPlaneSize, short PlaneStride, short PlaneHeight, const unsigned char* pYPlane, const unsigned char* pCPlane, CtImageType Type) :
	CtWidget(Size)
{
	ctor();
	setImage(Width, Height, YPlaneSize, PlaneStride, PlaneHeight, pYPlane, pCPlane, Type);
}
	
CtLabel::~CtLabel()
{
	if (m_pDrawInfo)	delete m_pDrawInfo;
}


bool CtLabel::setImage(const GDI_IMAGE_ID ImageID)
{
	return setImage(ImageID, CtColor::NoColor, CtColor::NoColor);
}

bool CtLabel::setImage(const GDI_IMAGE_ID ImageID, const CtColor& fillColor, const CtColor& edgeColor)
{
	GDI_IMAGE_BASE* pBase = GDI_GetImage(ImageID);
	bool bRet = false;

	if (pBase == NULL) return false;
	
	switch (pBase->type) {
	case GDI_IMAGE_TYPE_SVG:
		if (m_pDrawInfo == NULL) {
			m_pDrawInfo = new CtSVG(ImageID, fillColor, edgeColor);
			bRet = true;
			break;
		}
		if (m_pDrawInfo->getDrawType() == DrawType_SVG) {
			bRet = ((CtSVG*)m_pDrawInfo)->setSVG(ImageID, fillColor, edgeColor);
			break;
		} else {
			delete m_pDrawInfo;
			m_pDrawInfo = new CtSVG(ImageID, fillColor, edgeColor);
			bRet = true;
		}
		break;
	case GDI_IMAGE_TYPE_16BPP:
	case GDI_IMAGE_TYPE_32BPP:
		if (m_pDrawInfo == NULL) {
			m_pDrawInfo = new CtBitmap(ImageID);
			bRet = true;
			break;
		}
		if (m_pDrawInfo->getDrawType() == DrawType_Bitmap) {
			bRet = ((CtBitmap*)m_pDrawInfo)->setBitmap(ImageID);
			break;
		} else {
			delete m_pDrawInfo;
			m_pDrawInfo = new CtBitmap(ImageID);
			bRet = true;
		}
		break;
	default:
		return false;
	}
	
	if ((bRet == true) && (isVisible() == true))
		setInvalidate();
	
	return bRet;
}

GDI_IMAGE_ID CtLabel::getImageID()
{
	if ((m_pDrawInfo == NULL) || (m_pDrawInfo->getDrawType() != GDI_IMAGE_TYPE_SVG))
		return IMAGE_ID_INVALID;

	return ((CtSVG*)m_pDrawInfo)->getImageID();
}

bool CtLabel::setImage(short Width, short Height, short BufWidth, short BufHeight, const unsigned char* Data, CtImageType Type)
{
	bool bRet = false;

	if (Data == NULL)
		return bRet;
	
	if (m_pDrawInfo == NULL) {
		m_pDrawInfo = new CtBitmap(Width, Height, BufWidth, BufHeight, Data, Type);
		bRet = true;
		
	} else {
		if (m_pDrawInfo->getDrawType() != DrawType_Bitmap) {
			bRet = ((CtBitmap*)m_pDrawInfo)->setBitmap(Width, Height, BufWidth, BufHeight, Data, Type);
			
		} else {
			delete m_pDrawInfo;
			m_pDrawInfo = new CtBitmap(Width, Height, BufWidth, BufHeight, Data, Type);
			bRet = true;
		}
	}

	if ((bRet == true) && (isVisible() == true))
		setInvalidate();
	
	return bRet;
}

bool CtLabel::setImage(short Width, short Height, short YPlaneSize, short PlaneStride, short PlaneHeight, const unsigned char* pYPlane, const unsigned char* pCPlane, CtImageType Type)
{
	bool bRet = false;

	if ((pYPlane == NULL) || (pCPlane == NULL))
		return bRet;
	
	if (m_pDrawInfo == NULL) {
		m_pDrawInfo = new CtYUV(Width, Height, YPlaneSize, PlaneStride, PlaneHeight, pYPlane, pCPlane, Type);
		bRet = true;
		
	} else {
		if (m_pDrawInfo->getDrawType() == DrawType_Bitmap) {
			bRet = ((CtYUV*)m_pDrawInfo)->setYUV(Width, Height, YPlaneSize, PlaneStride, PlaneHeight, pYPlane, pCPlane, Type);
			
		} else {
			delete m_pDrawInfo;
			m_pDrawInfo = new CtYUV(Width, Height, YPlaneSize, PlaneStride, PlaneHeight, pYPlane, pCPlane, Type);
			bRet = true;
		}
	}
	
	if ((bRet == true) && (isVisible() == true))
		setInvalidate();
	
	return bRet;
}


bool CtLabel::setDrawable(const GDI_HANDLER DrawableID)
{
	bool bRet = false;
	
	if (m_pDrawInfo == NULL) {
		m_pDrawInfo = new CtDrawable(DrawableID);
		bRet = true;
		
	} else {
		if (m_pDrawInfo->getDrawType() == DrawType_Drawable) {
			bRet = ((CtDrawable*)m_pDrawInfo)->setDrawable(DrawableID);
			
		} else {
			delete m_pDrawInfo;
			m_pDrawInfo = new CtDrawable(DrawableID);
			bRet = true;
		}
	}

	if ((bRet == true) && (isVisible() == true))
		setInvalidate();

	return bRet;
}

bool CtLabel::setStringID(const GDI_STRING_ID StringID, const CtFontSet& FontSet)
{
	bool bRet = false;

	if (m_pDrawInfo == NULL) {
		m_pDrawInfo = new CtString(StringID, FontSet);
		bRet = true;
		
	} else {
		if (m_pDrawInfo->getDrawType() == DrawType_String) {
			bRet = ((CtString*)m_pDrawInfo)->setString(StringID, FontSet);

		} else {
			delete m_pDrawInfo;
			m_pDrawInfo = new CtString(StringID, FontSet);
			bRet = true;
		}
	}

	if ((bRet == true) && (isVisible() == true))
		setInvalidate();

	return bRet;
}

bool CtLabel::setStringID(const GDI_STRING_ID StringID)
{
	bool bRet = false;

	if (m_pDrawInfo == NULL) {
		m_pDrawInfo = new CtString(StringID);
		bRet = true;
		
	} else {
		if (m_pDrawInfo->getDrawType() == DrawType_String) {
			bRet = ((CtString*)m_pDrawInfo)->setString(StringID);
			
		} else {
			delete m_pDrawInfo;
			m_pDrawInfo = new CtString(StringID);
			bRet = true;
		}
	}

	if ((bRet == true) && (isVisible() == true))
		setInvalidate();

	return bRet;
}

bool CtLabel::setText(const char *ucStr, const CtFontSet& FontSet)
{
	bool bRet = false;

	if (ucStr == NULL)
		return false;
	
	if (m_pDrawInfo == NULL) {
		m_pDrawInfo = new CtString(ucStr, FontSet);
		bRet = true;
		
	} else {
		if (m_pDrawInfo->getDrawType() == DrawType_String) {
			bRet = ((CtString*)m_pDrawInfo)->setString(ucStr, FontSet);
		} else {
			delete m_pDrawInfo;
			m_pDrawInfo = new CtString(ucStr, FontSet);
			bRet = true;
		}
	}
			
	if ((bRet == true) && (isVisible() == true))
		setInvalidate();

	return true;
}

bool CtLabel::setText(const char *ucStr)
{
	bool bRet = false;

	if (ucStr == NULL)
		return false;
	
	if (m_pDrawInfo == NULL) {
		m_pDrawInfo = new CtString(ucStr);
		bRet = true;
		
	} else {
		if (m_pDrawInfo->getDrawType() == DrawType_String) {
			bRet = ((CtString*)m_pDrawInfo)->setString(ucStr);
		} else {
			delete m_pDrawInfo;
			m_pDrawInfo = new CtString(ucStr);
			bRet = true;
		}
	}
			
	if ((bRet == true) && (isVisible() == true))
		setInvalidate();

	return true;
}

bool CtLabel::setText(const unsigned short *ucStr, const CtFontSet& FontSet)
{
	bool bRet = false;

	if (ucStr == NULL)
		return false;
	
	if (m_pDrawInfo == NULL) {
		m_pDrawInfo = new CtString(ucStr, FontSet);
		bRet = true;
		
	} else {
		if (m_pDrawInfo->getDrawType() == DrawType_String) {
			bRet = ((CtString*)m_pDrawInfo)->setString(ucStr, FontSet);
		} else {
			delete m_pDrawInfo;
			m_pDrawInfo = new CtString(ucStr, FontSet);
			bRet = true;
		}
	}
			
	if ((bRet == true) && (isVisible() == true))
		setInvalidate();

	return true;
}

bool CtLabel::setText(const unsigned short *ucStr)
{
	bool bRet = false;

	if (ucStr == NULL)
		return false;
	
	if (m_pDrawInfo == NULL) {
		m_pDrawInfo = new CtString(ucStr);
		bRet = true;
		
	} else {
		if (m_pDrawInfo->getDrawType() == DrawType_String) {
			bRet = ((CtString*)m_pDrawInfo)->setString(ucStr);
		} else {
			delete m_pDrawInfo;
			m_pDrawInfo = new CtString(ucStr);
			bRet = true;
		}
	}
			
	if ((bRet == true) && (isVisible() == true))
		setInvalidate();

	return true;
}

unsigned short* CtLabel::getText()
{
	if ((m_pDrawInfo == NULL) || (m_pDrawInfo->getDrawType() != DrawType_String))
		return NULL;
	
	return ((CtString*)m_pDrawInfo)->getString();
}


bool CtLabel::setFontSet(const CtFontSet& FontSet)
{
	bool bRet = false;
	
	if ((m_pDrawInfo == NULL) ||(m_pDrawInfo->getDrawType() != DrawType_String))
		return false;

	bRet = ((CtString*)m_pDrawInfo)->setFontSet(FontSet);
	
	m_fillColor = FontSet.fontColor;
	m_edgeColor = FontSet.edgeColor;
	
	if ((bRet == true) && (isVisible() == true))
		setInvalidate();

	return true;
}

GDI_HANDLER CtLabel::getDrawable()
{
	return GDI_INVALID_ID;
}

bool CtLabel::setLine(const CtLine& Line)
{
	bool bRet = false;
	
	if (m_pDrawInfo == NULL) {
		m_pDrawInfo = new CtLine(Line);
		bRet = true;
		
	} else {
		if (m_pDrawInfo->getDrawType() == DrawType_Line) {
			if ((bRet = ((CtLine*)m_pDrawInfo)->setLine(Line)) != true) {
				return bRet;
			}
			
		} else {
			delete m_pDrawInfo;
			m_pDrawInfo = new CtLine(Line);
			bRet = true;
		}
	}
	
	if ((bRet == true) && (isVisible() == true)) {
		setInvalidate();
	}
	
	return bRet;
}

bool CtLabel::setLine(CtLineStyle Style, short lineWidth, const CtColor& lineColor)
{
	bool bRet = false;
	
	if (m_pDrawInfo == NULL) {
		m_pDrawInfo = new CtLine(Style, lineWidth, lineColor);
		bRet = true;
		
	} else {
		if (m_pDrawInfo->getDrawType() == DrawType_Line) {
			if ((bRet = ((CtLine*)m_pDrawInfo)->setLine(Style, lineWidth, lineColor)) != true) {
				return bRet;
			}
			
		} else {
			delete m_pDrawInfo;
			m_pDrawInfo = new CtLine(Style, lineWidth, lineColor);
			bRet = true;
		}
	}
	
	if ((bRet == true) && (isVisible() == true)) {
		setInvalidate();
	}
	return bRet;
}

bool CtLabel::setFill(const CtFill& Fill)
{
	bool bRet = false;
	
	if (m_pDrawInfo == NULL) {
		m_pDrawInfo = new CtFill(Fill);
		bRet = true;
		
	} else {
		if (m_pDrawInfo->getDrawType() == DrawType_Fill) {
			if ((bRet = ((CtFill*)m_pDrawInfo)->setFill(m_fillColor)) != true) {
				return bRet;
			}
			
		} else {
			delete m_pDrawInfo;
			m_pDrawInfo = new CtFill(Fill);
			bRet = true;
		}
	}
	
	if ((bRet == true) && (isVisible() == true)) {
		setInvalidate();
	}
	
	return bRet;
}

bool CtLabel::setRect(const CtRect& Rect)
{
	bool bRet = false;
	
	if (m_pDrawInfo == NULL) {
		m_pDrawInfo = new CtRect(Rect);
		bRet = true;
		
	} else {
		if (m_pDrawInfo->getDrawType() == DrawType_Rect) {
			if ((bRet = ((CtRect*)m_pDrawInfo)->setRect(Rect)) != true) {
				return bRet;
			}
			
		} else {
			delete m_pDrawInfo;
			m_pDrawInfo = new CtRect(Rect);
			bRet = true;
		}
	}
	
	if ((bRet == true) && (isVisible() == true)) {
		setInvalidate();
	}
	
	return bRet;
}

bool CtLabel::setRect(const CtColor& fillColor, short edgeWidth, const CtColor& edgeColor)
{
	bool bRet = false;
	
	if (m_pDrawInfo == NULL) {
		m_pDrawInfo = new CtRect(fillColor, edgeWidth, edgeColor);
		bRet = true;
		
	} else {
		if (m_pDrawInfo->getDrawType() == DrawType_Rect) {
			if ((bRet = ((CtRect*)m_pDrawInfo)->setRect(fillColor, edgeWidth, edgeColor)) != true) {
				return bRet;
			}
			
		} else {
			delete m_pDrawInfo;
			m_pDrawInfo = new CtRect(fillColor, edgeWidth, edgeColor);
			bRet = true;
		}
	}

	if ((bRet == true) && (isVisible() == true)) {
		setInvalidate();
	}
	
	return bRet;
}

bool CtLabel::setRoundRect(const CtRoundRect& RoundRect)
{
	bool bRet = false;
	
	if (m_pDrawInfo == NULL) {
		m_pDrawInfo = new CtRoundRect(RoundRect);
		bRet = true;
		
	} else {
		if (m_pDrawInfo->getDrawType() == DrawType_RoundRect) {
			if ((bRet = ((CtRoundRect*)m_pDrawInfo)->setRoundRect(RoundRect)) != true) {
				return bRet;
			}
			
		} else {
			delete m_pDrawInfo;
			m_pDrawInfo = new CtRoundRect(RoundRect);
			bRet = true;
		}
	}
	
	if ((bRet == true) && (isVisible() == true)) {
		setInvalidate();
	}
	
	return bRet;
}

bool CtLabel::setRoundRect(short ArcWidth, short ArcHeight, const CtColor& fillColor, short edgeWidth, const CtColor& edgeColor)
{
	bool bRet = false;
	
	if (m_pDrawInfo == NULL) {
		m_pDrawInfo = new CtRoundRect(ArcWidth, ArcHeight, fillColor, edgeWidth, edgeColor);
		bRet = true;
		
	} else {
		if (m_pDrawInfo->getDrawType() == DrawType_RoundRect) {
			if ((bRet = ((CtRoundRect*)m_pDrawInfo)->setRoundRect(ArcWidth, ArcHeight, fillColor, edgeWidth, edgeColor)) != true) {
				return bRet;
			}
			
		} else {
			delete m_pDrawInfo;
			m_pDrawInfo = new CtRoundRect(ArcWidth, ArcHeight, fillColor, edgeWidth, edgeColor);
			bRet = true;
		}
	}

	if ((bRet == true) && (isVisible() == true)) {
		setInvalidate();
	}
	
	return bRet;
}

bool CtLabel::setEllipse(const CtEllipse& Ellipse)
{
	bool bRet = false;
	
	if (m_pDrawInfo == NULL) {
		m_pDrawInfo = new CtEllipse(Ellipse);
		bRet = true;
		
	} else {
		if (m_pDrawInfo->getDrawType() == DrawType_Ellipse) {
			if ((bRet = ((CtEllipse*)m_pDrawInfo)->setEllipse(Ellipse)) != true) {
				return bRet;
			}
			
		} else {
			delete m_pDrawInfo;
			m_pDrawInfo = new CtEllipse(Ellipse);
			bRet = true;
		}
	}
	
	if ((bRet == true) && (isVisible() == true)) {
		setInvalidate();
	}
	
	return bRet;
}

bool CtLabel::setEllipse(const CtColor& fillColor, short edgeWidth, const CtColor& edgeColor)
{
	bool bRet = false;
	
	if (m_pDrawInfo == NULL) {
		m_pDrawInfo = new CtEllipse(fillColor, edgeWidth, edgeColor);
		bRet = true;
		
	} else {
		if (m_pDrawInfo->getDrawType() == DrawType_Ellipse) {
			if ((bRet = ((CtEllipse*)m_pDrawInfo)->setEllipse(fillColor, edgeWidth, edgeColor)) != true) {
				return bRet;
			}
			
		} else {
			delete m_pDrawInfo;
			m_pDrawInfo = new CtEllipse(fillColor, edgeWidth, edgeColor);
			bRet = true;
		}
	}
	
	if ((bRet == true) && (isVisible() == true)) {
		setInvalidate();
	}
	
	return bRet;
}

bool CtLabel::setColor(const CtColor& fillColor)
{
	bool bRet = false;

	if (m_bFixedColor == true)
		return bRet;

	if (m_fillColor == fillColor)
		return bRet;
	
	m_fillColor = fillColor;

	if (m_pDrawInfo == NULL) {
		m_pDrawInfo = new CtFill(m_fillColor);
		bRet = true;
		
	} else {
		bRet = m_pDrawInfo->setColor(m_fillColor);
	}
	
	if ((bRet == true) && (isVisible() == true)) {
		setInvalidate();
	}
	
    return bRet;
}

bool CtLabel::setColor(const CtColor& fillColor, const CtColor& edgeColor)
{
	bool bRet = false;

	if (m_bFixedColor == true)
		return bRet;

	if ((m_fillColor == fillColor) && (m_edgeColor == edgeColor))
		return bRet;


	m_fillColor = fillColor;
	m_edgeColor = edgeColor;
	
	if (m_pDrawInfo == NULL) {
		m_pDrawInfo = new CtRect(m_fillColor, 2, m_edgeColor);
		bRet = true;

	} else {
		bRet = m_pDrawInfo->setColor(m_fillColor, m_edgeColor);
	}
	
	if ((bRet == true) && (isVisible() == true)) {
		setInvalidate();
	}
	
    return bRet;
}

CtColor CtLabel::getColor() const
{
	if (m_fillColor != CtColor::NoColor)
		return m_fillColor;

	switch (m_pDrawInfo->getDrawType()) {
	case DrawType_Fill:
	case DrawType_Rect:
	case DrawType_RoundRect:
	case DrawType_Ellipse:
		return m_pDrawInfo->getFillColor();
	default:
		break;
	}
	return CtColor::NoColor;
}

CtDrawInfo* CtLabel::getDrawInfo(const CtRegion& Clip, int Screen)
{
	CtRegion clip = Clip;
	
	if (m_pDrawInfo == NULL)
		return NULL;

	if (clip == NoRegion)
		return m_pDrawInfo;
	
	clip &= m_Region[Screen];

	if (clip.isValid() != true)
		return NULL;
	
	m_ClearRegion[Screen] = m_Region[Screen];
	
	m_pDrawInfo->setRegion(m_Region[Screen]);
	m_pDrawInfo->setClip(clip);
	m_pDrawInfo->setTrans(isTrans());
	
	return m_pDrawInfo;
}

bool CtLabel::getDrawInfo(CtList::list<CtDrawInfo*> &List, const CtRegion& Clip, int Screen)
{
	CtDrawInfo* pDrawInfo = NULL;

	if ((pDrawInfo = getDrawInfo(Clip, Screen)) != NULL) {
		List.push_back(pDrawInfo);
		return true;
	}
	
	return false;
}

bool CtLabel::isFastDraw() const
{
	return m_bFastDraw;
}

bool CtLabel::setFastDraw(bool bFast)
{
	if (m_bFastDraw == bFast)
		return false;
	
	m_bFastDraw = bFast;
	return true;
}

bool CtLabel::initialFastDraw()
{
	if (isFastDraw() != true)
		return false;

	if ((m_Region[0].isValid() != true) && (m_Size.isValid() != true))
		return false;

	if (m_Region[0].isValid() != true)
		m_Region[0] = CtRegion(0, 0, m_Size.width, m_Size.height);
	
	return setDrawImage();
}

bool CtLabel::cleanupFastDraw()
{
	if (m_pDrawInfo == NULL)
		return false;
	
	return m_pDrawInfo->setDrawImage(GDI_INVALID_ID);
}

bool CtLabel::setFixedColor(bool bFixed)
{
	if (m_bFixedColor == bFixed)
		return false;

	m_bFixedColor = bFixed;
	return true;
}

bool CtLabel::handleParamEvent(const CtEventParam& Param)
{
	if (AplParamLanguage != Param.getParamId())
		return false;


	if ((m_pDrawInfo == NULL) || (m_pDrawInfo->getDrawType() != DrawType_String))
		return false;

	bool bRet = ((CtString*)m_pDrawInfo)->updeteLanguage();

	if ((bRet == true) && (isVisible() == true))
		setInvalidate();

	return bRet;
}
