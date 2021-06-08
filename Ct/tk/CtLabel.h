/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtLabel
 */


#ifndef __CtLabel_H__
#define __CtLabel_H__

#include "gdi.h"
#include "Ct.h"
#include "CtWidget.h"
#include "CtColor.h"

class CtLabel : public CtWidget {
    ////    Constructors and destructors    ////
    
public :
    virtual ~CtLabel();

	CtLabel();
	CtLabel(const CtColor& Color);
	CtLabel(const CtSize& Size);
	CtLabel(const CtRegion& Region);
	//	CtLabel(const CtLabel& Label);

    CtLabel(const GDI_IMAGE_ID ImageID);
    CtLabel(const GDI_IMAGE_ID ImageID, const CtColor& fillColor, const CtColor& edgeColor = CtColor::NoColor);
	CtLabel(const GDI_HANDLER DrawableID);
    CtLabel(const GDI_STRING_ID StringID, const CtFontSet& FontSet);
    CtLabel(const GDI_STRING_ID StringID);
	CtLabel(const char* ucStr, const CtFontSet& FontSet);
	CtLabel(const char* ucStr);
	CtLabel(const unsigned short* ucStr, const CtFontSet& FontSet);
	CtLabel(const unsigned short* ucStr);
	CtLabel(const CtLine& Line);
	CtLabel(const CtRect& Rect);
	CtLabel(const CtFill& Fill);
	CtLabel(const CtRoundRect& RoundRect);
	CtLabel(const CtEllipse& Ellipse);
	CtLabel(short Width, short Height, short BufWidth, short BufHeight, const unsigned char* Data, CtImageType Type);
	CtLabel(short Width, short Height, short YPlaneSize, short PlaneStride, short PlaneHeight, const unsigned char* pYPlane, const unsigned char* pCPlane, CtImageType Type);
	
	CtLabel(const CtSize& Size, const CtColor& Color);
    CtLabel(const CtSize& Size, const GDI_IMAGE_ID ImageID);
    CtLabel(const CtSize& Size, const GDI_IMAGE_ID ImageID, const CtColor& fillColor, const CtColor& edgeColor = CtColor::NoColor);
	CtLabel(const CtSize& Size, const GDI_HANDLER DrawableID);
    CtLabel(const CtSize& Size, const GDI_STRING_ID StringID, const CtFontSet& FontSet);
    CtLabel(const CtSize& Size, const GDI_STRING_ID StringID);
	CtLabel(const CtSize& Size, const char* ucStr, const CtFontSet& FontSet);
	CtLabel(const CtSize& Size, const char* ucStr);
	CtLabel(const CtSize& Size, const unsigned short* ucStr, const CtFontSet& FontSet);
	CtLabel(const CtSize& Size, const unsigned short* ucStr);
	CtLabel(const CtSize& Size, const CtLine& Line);
	CtLabel(const CtSize& Size, const CtRect& Rect);
	CtLabel(const CtSize& Size, const CtFill& Fill);
	CtLabel(const CtSize& Size, const CtRoundRect& RoundRect);
	CtLabel(const CtSize& Size, const CtEllipse& Ellipse);
	CtLabel(const CtSize& Size, short Width, short Height, short BufWidth, short BufHeight, const unsigned char* Data, CtImageType Type);
	CtLabel(const CtSize& Size, short Width, short Height, short YPlaneSize, short PlaneStride, short PlaneHeight, const unsigned char* pYPlane, const unsigned char* pCPlane, CtImageType Type);

	virtual bool setImage(const GDI_IMAGE_ID ImageID);
	virtual bool setImage(const GDI_IMAGE_ID ImageID, const CtColor& fillColor, const CtColor& edgeColor);
	virtual bool setImage(short Width, short Height, short BufWidth, short BufHeight, const unsigned char* Data, CtImageType Type);
	virtual bool setImage(short Width, short Height, short YPlaneSize, short PlaneStride, short PlaneHeight, const unsigned char* pYPlane, const unsigned char* pCPlane, CtImageType Type);
	virtual GDI_IMAGE_ID getImageID();
	
	virtual bool setDrawable(const GDI_HANDLER DrawableID);
	virtual GDI_HANDLER getDrawable();
	
	virtual bool setFontSet(const CtFontSet& FontSet);
	
	virtual bool setStringID(const GDI_STRING_ID, const CtFontSet& FontSet);
	virtual bool setStringID(const GDI_STRING_ID);
	
	virtual bool setText(const char *ucStr);
	virtual bool setText(const char *ucStr, const CtFontSet& FontSet);
	virtual bool setText(const unsigned short *ucStr);
	virtual bool setText(const unsigned short *ucStr, const CtFontSet& FontSet);
	virtual unsigned short* getText();
	
	virtual bool setLine(const CtLine& Line);
	virtual bool setLine(CtLineStyle Style, short lineWidth, const CtColor& lineColor);
	
	virtual bool setFill(const CtFill& Fill);
	virtual bool setRect(const CtRect& Rect);
	virtual bool setRect(const CtColor& fillColor, short edgeWidth, const CtColor& edgeColor = CtColor::NoColor);
	
	virtual bool setRoundRect(const CtRoundRect& RoundRect);
	virtual bool setRoundRect(short ArcWidth, short ArcHeight, const CtColor& fillColor, short edgeWidth, const CtColor& edgeColor = CtColor::NoColor);
	
	virtual bool setEllipse(const CtEllipse& Ellipse);
	virtual bool setEllipse(const CtColor& fillColor, short edgeWidth, const CtColor& edgeColor = CtColor::NoColor);

	virtual bool setColor(const CtColor& fillColor);
	virtual bool setColor(const CtColor& fillColor, const CtColor& edgeColor);
	CtColor getColor() const;
	
	virtual CtDrawInfo* getDrawInfo(const CtRegion& Clip = NoRegion, int Screen = 0);
	virtual bool getDrawInfo(CtList::list<CtDrawInfo*> &List, const CtRegion& Clip = NoRegion, int Screen = 0);
	inline virtual bool isLabel() const;

	bool isFastDraw() const;
	bool setFastDraw(bool bFast);
	bool initialFastDraw();
	bool cleanupFastDraw();
	bool setFixedColor(bool bFixed);

	virtual bool handleParamEvent(const CtEventParam& Param);

protected:
	void ctor();
	
	CtColor			m_fillColor;
	CtColor			m_edgeColor;
	bool			m_bFixedColor;

	CtDrawInfo*		m_pDrawInfo;
	bool			m_bFastDraw;
};

inline bool CtLabel::isLabel() const
{
	return true;
}

#endif
