/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtDrawInfo
 */

#include "Ct.h"
#include "CtColor.h"

#include "gdi.h"
#include "utf_convert.h"
#include "language_id.h"

#ifndef __CtDrawInfo_H__
#define __CtDrawInfo_H__

#define CT_FONT_ALIGN_MASK		(0xF000)
#define CT_FONT_VALIGN_MASK		(0x0F00)
#define CT_FONT_TYPE_MASK		(0x00FF)
#define CT_FONT_VALIGN_TOP		(0x0100)
#define CT_FONT_VALIGN_MIDDLE	(0x0200)
#define CT_FONT_VALIGN_BOTTOM	(0x0400)
#define CT_FONT_ALIGN_LEFT		(0x1000)
#define CT_FONT_ALIGN_CENTER	(0x2000)
#define CT_FONT_ALIGN_RIGHT		(0x4000)
#define CT_FONT_ALIGN_AUTO		(0x8000)

enum FontSetType {
	//左揃え（縦位置は自動(中央やや下くらいに来る。余白部分を下に25%、上75%で割り振っている）
	FontTypeNormal = 0x0000 | CT_FONT_ALIGN_LEFT,
	FontTypeBold,
	FontTypeOutline,
	FontTypeMono,

	//中央揃え（縦位置は自動）
	FontTypeNormal_alignCenter = 0x0000 | CT_FONT_ALIGN_CENTER,
	FontTypeBold_alignCenter,
	FontTypeOutline_alignCenter,
	FontTypeMono_alignCenter,

	//右揃え（縦位置は自動）
	FontTypeNormal_alignRight = 0x0000 | CT_FONT_ALIGN_RIGHT,
	FontTypeBold_alignRight,
	FontTypeOutline_alignRight,
	FontTypeMono_alignRight,

	//上・左揃え
	FontTypeNormal_Top = FontTypeNormal | CT_FONT_VALIGN_TOP,
	FontTypeBold_Top,
	FontTypeOutline_Top,
	FontTypeMono_Top,

	//上・中央揃え
	FontTypeNormal_alignCenter_Top = FontTypeNormal_alignCenter | CT_FONT_VALIGN_TOP,
	FontTypeBold_alignCenter_Top,
	FontTypeOutline_alignCenter_Top,
	FontTypeMono_alignCenter_Top,

	//上・右揃え
	FontTypeNormal_alignRight_Top = FontTypeNormal_alignRight | CT_FONT_VALIGN_TOP,
	FontTypeBold_alignRight_Top,
	FontTypeOutline_alignRight_Top,
	FontTypeMono_alignRight_Top,

	//中央・左揃え
	FontTypeNormal_Middle = FontTypeNormal | CT_FONT_VALIGN_MIDDLE,
	FontTypeBold_Middle,
	FontTypeOutline_Middle,
	FontTypeMono_Middle,

	//中央・中央揃え
	FontTypeNormal_alignCenter_Middle = FontTypeNormal_alignCenter | CT_FONT_VALIGN_MIDDLE,
	FontTypeBold_alignCenter_Middle,
	FontTypeOutline_alignCenter_Middle,
	FontTypeMono_alignCenter_Middle,

	//中央・右揃え
	FontTypeNormal_alignRight_Middle = FontTypeNormal_alignRight | CT_FONT_VALIGN_MIDDLE,
	FontTypeBold_alignRight_Middle,
	FontTypeOutline_alignRight_Middle,
	FontTypeMono_alignRight_Middle,

	//下・左揃え
	FontTypeNormal_Bottom = FontTypeNormal | CT_FONT_VALIGN_BOTTOM,
	FontTypeBold_Bottom,
	FontTypeOutline_Bottom,
	FontTypeMono_Bottom,

	//下・中央揃え
	FontTypeNormal_alignCenter_Bottom = FontTypeNormal_alignCenter | CT_FONT_VALIGN_BOTTOM,
	FontTypeBold_alignCenter_Bottom,
	FontTypeOutline_alignCenter_Bottom,
	FontTypeMono_alignCenter_Bottom,

	//下・右揃え
	FontTypeNormal_alignRight_Bottom = FontTypeNormal_alignRight | CT_FONT_VALIGN_BOTTOM,
	FontTypeBold_alignRight_Bottom,
	FontTypeOutline_alignRight_Bottom,
	FontTypeMono_alignRight_Bottom,

	// アライメントはWidgetのレイアウトに従う
	FontTypeNormal_alignAuto = 0x0000 | CT_FONT_ALIGN_AUTO,
	FontTypeBold_alignAuto,
	FontTypeOutline_alignAuto,
	FontTypeMono_alignAuto,
	
	FontTypeMax
};

class CtFontSet : public CtObject {
public:
	CtFontSet();
	CtFontSet(const CtColor& _color);
	CtFontSet(FontSetType _type);
	CtFontSet(FontSetType _type, const CtColor& _fontColor);
	CtFontSet(FontSetType _type, const CtColor& _fontColor, const CtColor& _edgeColor);
	virtual ~CtFontSet();

	bool setSize(short _size);
	bool setColor(const CtColor& _fontColor, const CtColor& _edgeColor);
	bool setColor(const CtColor& _fontColor);
	bool setStrokeWidth(short _stroke_width);
	bool setEdgeColor(CtColor& _edgeColor);
	bool setFontAttribute(FontSetType _type);
	bool setAlign(CtAlign _align);
	bool setLocale(FONT_LOCALE _locale);
	bool setLanguageId(LANGUAGE_ID _language);
	LANGUAGE_ID getLanguageId();
	bool setAspectRatio(CtAspectRatio _ratio);
	bool setAutoAdjust(bool _adjust);
	bool setFontSet(const CtFontSet &_fontset);
	bool isSame(const CtFontSet& _fontset);
	
	bool getStringSize(CtSize& Size, const char* pStr);
	bool getStringSize(CtSize& Size, const unsigned short* pStr);
	bool getStringSize(CtSize& Size, GDI_STRING_ID stringId);
	
	CtFontSet& operator=(const CtFontSet &_fontset);
	
protected:
	void ctor();
	
public:
	LANGUAGE_ID		languageID;
	GDI_FONT_STYLE	fontStyle;
	CtColor			fontColor;
	CtColor			edgeColor;
	short			strokeWidth;
};

class CtRecViewFontSet : public CtFontSet {
public:
	CtRecViewFontSet();
	CtRecViewFontSet(FontSetType _type);
	CtRecViewFontSet(FontSetType _type, const CtColor& _fontColor);
	CtRecViewFontSet(FontSetType _type, const CtColor& _fontColor, const CtColor& _edgeColor);
	void setFontAttribute(FontSetType _type);
	
private:
	void ctor();
};


enum CtDrawType {
	DrawType_None,
	DrawType_Fill,
	DrawType_SVG,
	DrawType_Bitmap,
	DrawType_YUV,
	DrawType_Drawable,
	DrawType_String,
	DrawType_Line,
	DrawType_Rect,
	DrawType_RoundRect,
	DrawType_Ellipse,
	DrawType_Font,
	DrawType_MAX
};

enum CtImageType {
	ImageType_16BPP,
	ImageType_32BPP,
	ImageType_YUV420,
	ImageType_YUV422
};


class CtDrawInfo : public CtObject {
public:
	CtDrawInfo();
	virtual ~CtDrawInfo();

	CtDrawType getDrawType() const;

	virtual bool setRegion(const CtRegion& _region);
	virtual bool setRegion(short _x, short _y, short _width, short _height);
	virtual bool getRegion(CtRegion& _region);
	virtual bool setClip(const CtRegion& _region);
	virtual bool setClip(short _x, short _y, short _width, short _height);
	virtual bool getClip(CtRegion& _clip);
	virtual bool setPos(const CtPosition& _position);
	virtual bool setPos(short _x, short _y);
	virtual bool movePos(const CtPosition& _position);
	virtual bool movePos(short _x, short _y);
	virtual bool setTrans(bool bTrans);
	virtual bool isTrans() const;

	virtual bool setColor(GDI_COLOR* pColor, const CtColor& Color);
	virtual CtColor getColor(const GDI_COLOR* pColor) const;
	virtual bool isSame(GDI_COLOR* pColor, const CtColor& Color);
	virtual bool setColor(const CtColor& fillColor);
	virtual bool setColor(const CtColor& fillColor, const CtColor& edgeColor);
	virtual CtColor getFillColor() const;
	virtual CtColor getEdgeColor() const;
	
	virtual bool setAlign(CtAlign _align);
	virtual bool setAspectRatio(CtAspectRatio _ratio);
	virtual bool setAutoAdjust(bool _adjust);
	
	bool setDrawImage(GDI_HANDLER id);
	void lostDrawImage();
	bool haveDrawImage() const;
	GDI_HANDLER getDrawImage();
	virtual bool draw();
	virtual bool drawFast();
	virtual unsigned long getDrawKey();
	virtual unsigned long getPathKey();
	virtual void lostCache();
	static unsigned long calcKey(unsigned long key1, unsigned long key2);

protected:
	static unsigned long calcCRC(unsigned long base, const unsigned char* data, unsigned int size);
	
	CtDrawType		m_Type;
	bool			m_bFast;

	static const unsigned long m_CrcTable[256];
	static const unsigned int m_CrcTableNum;

public:
	GDI_DRAW_BASE	m_Base;
	GDI_HANDLER		m_DrawImage;
};


inline CtDrawType CtDrawInfo::getDrawType() const
{
	return m_Type;
}

inline bool CtDrawInfo::draw()
{
	return false;
}

inline void CtDrawInfo::lostCache()
{
	return;
}

class CtString : public CtDrawInfo {
public:
	CtString();
	CtString(const GDI_STRING_ID _id);
	CtString(const GDI_STRING_ID _id, const CtFontSet& _fontset);
	CtString(const char* _pstr);
	CtString(const char* _pstr, const CtFontSet& _fontset);
	CtString(const unsigned short* _pstr);
	CtString(const unsigned short* _pstr, const CtFontSet& _fontset);
	virtual ~CtString();

	bool setString(const GDI_STRING_ID _id, const CtFontSet& _fontset);
	bool setString(const GDI_STRING_ID _id);
	bool setString(const char* _pstr, const CtFontSet& _fontset);
	bool setString(const char* _pstr);
	bool setString(const unsigned short* _pstr, const CtFontSet& _fontset);
	bool setString(const unsigned short* _pstr, bool bChangeid = true);
	unsigned short* getString();
	CtRegion getRect();
	bool updeteLanguage();

	bool setAlign(CtAlign _align);
	bool setAspectRatio(CtAspectRatio _ratio);
	bool setAutoAdjust(bool _adjust);
	
	bool setFontSet(const CtFontSet& _fontset);
	CtFontSet getFontSet() const;
	bool setSize(short _size);
	bool setEdgeColor(CtColor& _edgeColor);
	bool setFontAttribute(FontSetType _type);
	bool setLocale(FONT_LOCALE _locale);
	bool setLanguageId(LANGUAGE_ID _language);

	bool setColor(const CtColor& _fontcolor);
	bool setColor(const CtColor& _fontcolor, const CtColor& _edgecolor);
	bool setStrokeWidth(short _stroke_width);
	CtColor getFillColor() const;
	CtColor getEdgeColor() const;
	bool draw();
	unsigned long getDrawKey();
	unsigned long getPathKey();
	void lostCache();

private:
	bool setFontStyle(GDI_FONT_STYLE _fontstyle);
	
private:
	void ctor();
	
	GDI_STRING_ID	m_id;
	LANGUAGE_ID		m_languageID;
	unsigned short	m_bufSize;
	CtColor			m_fontColor;
	CtColor			m_edgeColor;
	short			m_StrokeWidth;
	//	CtFontSet		m_FontSet;
	
public:
	GDI_DRAW_FONT	m_String;
	GDI_CACHE_FONT*	m_pCache;
};

class CtDrawable : public CtDrawInfo {
public:
	CtDrawable();
	CtDrawable(const GDI_HANDLER _id);
	
	bool setDrawable(const GDI_HANDLER _id);

	bool setAlign(CtAlign _align);
	bool setAspectRatio(CtAspectRatio _ratio);
	bool setAutoAdjust(bool _adjust);
	
	bool draw();
	unsigned long getDrawKey();

	GDI_DRAW_DRAWABLE	m_Draw;
};


class CtFill : public CtDrawInfo {
public:
	CtFill();
	CtFill(const CtColor& _color);
	CtFill(const CtRegion& _region, const CtColor& _color);
	bool setFill(const CtColor& _color);
	bool setFill(const CtRegion& _region, const CtColor& _color);
	bool setColor(const CtColor& Color);
	CtColor getFillColor() const;
	bool draw();
	bool drawFast();
	unsigned long getDrawKey();
	
private:
	void ctor();
	
public:
	GDI_COLOR	m_Color;
};


class CtSVG : public CtDrawInfo {
public:
	CtSVG();
	CtSVG(const GDI_IMAGE_ID _id, const CtColor& _fillColor, const CtColor& _edgeColor);
	virtual ~CtSVG();
	bool setSVG(const GDI_IMAGE_ID _id, const CtColor& _fillColor, const CtColor& _edgeColor);
	bool setColor(const CtColor& _fill_color);
	bool setColor(const CtColor& _fill_color, const CtColor& _edge_color);
	GDI_IMAGE_ID  getImageID() const {return m_id;}
	GDI_IMAGE_SVG* getSVG();
	
	bool setAlign(CtAlign _align);
	bool setAspectRatio(CtAspectRatio _ratio);
	bool setAutoAdjust(bool _adjust);
	
	bool draw();
	unsigned long getDrawKey();
	unsigned long getPathKey();
	void lostCache();
	
private:
	void ctor();
	
	CtColor			m_fillColor;
	CtColor			m_edgeColor;
	
public:
	GDI_IMAGE_ID	m_id;
	GDI_DRAW_SVG	m_Draw;
	
	GDI_CACHE_SVG*	m_pCache;
};

class CtBitmap : public CtDrawInfo {
public:
	CtBitmap();
	CtBitmap(const GDI_IMAGE_ID _id);
	CtBitmap(short _width, short _height, short _buf_width, short _buf_height, const unsigned char* _data, CtImageType _type = ImageType_32BPP);
	bool setBitmap(const GDI_IMAGE_ID _id);
	bool setBitmap(short _width, short _height, short _buf_width, short _buf_height, const unsigned char* _data, CtImageType _type = ImageType_32BPP);
	GDI_IMAGE_ID getImageID() const {return m_id;}
	GDI_IMAGE_BITMAP* getBitmap();

	bool setAlign(CtAlign _align);
	bool setAspectRatio(CtAspectRatio _ratio);
	bool setAutoAdjust(bool _adjust);
	
	bool draw();
	unsigned long getDrawKey();
	
private:
	GDI_IMAGE_ID		m_id;
public:
	GDI_DRAW_BITMAP		m_Draw;
};

class CtYUV : public CtDrawInfo {
public:
	CtYUV();
	CtYUV(short _width, short _height, short _y_plane_size, short _plane_stride, short _plane_height, const unsigned char* _y_plane, const unsigned char* _c_plane, CtImageType _type = ImageType_YUV422);
	bool setYUV(short _width, short _height, short _y_plane_size, short _plane_stride, short _plane_height, const unsigned char* _y_plane, const unsigned char* _c_plane, CtImageType _type = ImageType_YUV422);
	
	bool setAlign(CtAlign _align);
	bool setAspectRatio(CtAspectRatio _ratio);
	bool setAutoAdjust(bool _adjust);
	
	bool draw();
	unsigned long getDrawKey();
	
public:
	GDI_DRAW_YUV		m_Draw;
};

enum CtLineStyle {
	UnderLine,
	UpperLine,
	LeftLine,
	RightLine,
	TopLeftSlashLine,
	TopRightSlashLine,
	NonStyleLine
};

class CtLine : public CtDrawInfo {
public:
	CtLine();
	CtLine(CtLineStyle _style);
	CtLine(short _stroke_width);
	CtLine(CtLineStyle _style, short _stroke_width);
	CtLine(CtLineStyle _style, short _stroke_width, const CtColor& _color);

	bool setLine(CtLineStyle _style, short _stroke_width, const CtColor& _color);
	bool setLine(const CtLine& Line);
	bool setRegion(short _x, short _y, short _width, short _height);
	
	bool setLineStyle(CtLineStyle _style);
	bool setStrokeWidth(short _stroke_width);
	bool setColor(const CtColor& _fill_color, const CtColor& _stroke_color);
	bool setColor(const CtColor& _color);
	CtColor getFillColor() const;
	
	bool draw();
	unsigned long getDrawKey();

private:
	void ctor();

	CtLineStyle		m_LineStyle;
	CtColor			m_lineColor;
	
public:
	GDI_DRAW_LINE	m_Line;
};


class CtRect : public CtDrawInfo {
public:
	CtRect();
	CtRect(const CtColor& _fill_color);
	CtRect(short _stroke_width, const CtColor& _stroke_color);
	CtRect(const CtColor& _fill_color, short _stroke_width, const CtColor& _stroke_color);
	
	bool setRect(const CtColor& _fill_color, short _stroke_width, const CtColor& _stroke_color);
	bool setRect(const CtRect& Rect);
	
	bool setStrokeWidth(short _stroke_width);
	bool setColor(const CtColor& _fill_color, const CtColor& _stroke_color);
	bool setColor(const CtColor& _fill_color);
	CtColor getFillColor() const;
	CtColor getEdgeColor() const;
	
	bool draw();
	unsigned long getDrawKey();
	
private:
	void ctor();
	CtColor				m_fillColor;
	CtColor				m_edgeColor;
	
public:	
	GDI_DRAW_RECT		m_Rect;
};

class CtRoundRect : public CtDrawInfo {
public:
	CtRoundRect();
	CtRoundRect(const CtColor& _fill_color);
	CtRoundRect(short _stroke_width, const CtColor& _stroke_color);
	CtRoundRect(const CtColor& _fill_color, short _stroke_width, const CtColor& _stroke_color);
	CtRoundRect(short _arc_width, short _arc_height, const CtColor& _fill_color, short _stroke_width, const CtColor& _stroke_color);

	bool setRoundRect(short _arc_width, short _arc_height, const CtColor& _fill_color, short _stroke_width, const CtColor& _stroke_color);
	bool setRoundRect(const CtRoundRect& RoundRect);
	
	bool setStrokeWidth(short _stroke_width);
	bool setArc(short _arc_width, short _arc_height);
	bool setColor(const CtColor& _fill_color, const CtColor& _stroke_color);
	bool setColor(const CtColor& _fill_color);
	CtColor getFillColor() const;
	CtColor getEdgeColor() const;
	
	bool draw();
	unsigned long getDrawKey();
	
private:
	void ctor();
	CtColor				m_fillColor;
	CtColor				m_edgeColor;

public:
	GDI_DRAW_ROUNDRECT	m_RRect;
};

class CtEllipse : public CtDrawInfo {
public:
	CtEllipse();
	CtEllipse(const CtColor& _fill_color);
	CtEllipse(short _stroke_width, const CtColor& _stroke_color);
	CtEllipse(const CtColor& fillColor, short _stroke_width, const CtColor& _stroke_color);
	
	bool setEllipse(const CtColor& fillColor, short _stroke_width, const CtColor& _stroke_color);
	bool setEllipse(const CtEllipse& Ellipse);
	
	bool setStrokeWidth(short _stroke_width);
	bool setColor(const CtColor& _fill_color, const CtColor& _stroke_color);
	bool setColor(const CtColor& _fill_color);
	CtColor getFillColor() const;
	CtColor getEdgeColor() const;
	
	bool draw();
	unsigned long getDrawKey();
	
private:
	void ctor();
	CtColor				m_fillColor;
	CtColor				m_edgeColor;

public:
	GDI_DRAW_ELLIPSE	m_Ellipse;
};

#endif
