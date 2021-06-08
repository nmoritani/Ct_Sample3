/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtParamIcon
 */


#ifndef __CtParamIcon_H__
#define __CtParamIcon_H__

#include "CtLabel.h"

class CtParamIcon : public CtLabel {
    ////    Constructors and destructors    ////
    
public :
    virtual ~CtParamIcon();

	CtParamIcon();
	CtParamIcon(const CtSize& Size);
	CtParamIcon(const CtRegion& Region);

	CtParamIcon(const CtColor& Color);
    CtParamIcon(const GDI_IMAGE_ID ImageID);
    CtParamIcon(const GDI_IMAGE_ID ImageID, const CtColor& fillColor, const CtColor& edgeColor = CtColor::NoColor);
	CtParamIcon(const GDI_HANDLER DrawableID);
    CtParamIcon(const GDI_STRING_ID StringID, const CtFontSet& FontSet);
    CtParamIcon(const GDI_STRING_ID StringID);
	CtParamIcon(const char* ucStr, const CtFontSet& FontSet);
	CtParamIcon(const char* ucStr);
	CtParamIcon(const unsigned short* ucStr, const CtFontSet& FontSet);
	CtParamIcon(const unsigned short* ucStr);
	CtParamIcon(const CtLine& Line);
	CtParamIcon(const CtRect& Rect);
	CtParamIcon(const CtFill& Fill);
	CtParamIcon(const CtRoundRect& RoundRect);
	CtParamIcon(const CtEllipse& Ellipse);
	CtParamIcon(short Width, short Height, short BufWidth, short BufHeight, const unsigned char* Data, CtImageType Type);
	CtParamIcon(short Width, short Height, short YPlaneSize, short PlaneStride, short PlaneHeight, const unsigned char* pYPlane, const unsigned char* pCPlane, CtImageType Type);
	
	CtParamIcon(const CtSize& Size, const CtColor& Color);
    CtParamIcon(const CtSize& Size, const GDI_IMAGE_ID ImageID);
    CtParamIcon(const CtSize& Size, const GDI_IMAGE_ID ImageID, const CtColor& fillColor, const CtColor& edgeColor = CtColor::NoColor);
	CtParamIcon(const CtSize& Size, const GDI_HANDLER DrawableID);
    CtParamIcon(const CtSize& Size, const GDI_STRING_ID StringID, const CtFontSet& FontSet);
    CtParamIcon(const CtSize& Size, const GDI_STRING_ID StringID);
	CtParamIcon(const CtSize& Size, const char* ucStr, const CtFontSet& FontSet);
	CtParamIcon(const CtSize& Size, const char* ucStr);
	CtParamIcon(const CtSize& Size, const unsigned short* ucStr, const CtFontSet& FontSet);
	CtParamIcon(const CtSize& Size, const unsigned short* ucStr);
	CtParamIcon(const CtSize& Size, const CtLine& Line);
	CtParamIcon(const CtSize& Size, const CtRect& Rect);
	CtParamIcon(const CtSize& Size, const CtRoundRect& RoundRect);
	CtParamIcon(const CtSize& Size, const CtEllipse& Ellipse);
	CtParamIcon(const CtSize& Size, short Width, short Height, short BufWidth, short BufHeight, const unsigned char* Data, CtImageType Type);
	CtParamIcon(const CtSize& Size, short Width, short Height, short YPlaneSize, short PlaneStride, short PlaneHeight, const unsigned char* pYPlane, const unsigned char* pCPlane, CtImageType Type);
	
	virtual CtDrawInfo* getDrawInfo(const CtRegion& Clip, int Screen = 0);
	bool setParam(int ParamID, int ParamData);
	bool handleParamEvent(const CtEventParam& Param);
	
protected:
	void ctor();
	int		m_ParamId;
	int		m_ParamData;
};

#endif
