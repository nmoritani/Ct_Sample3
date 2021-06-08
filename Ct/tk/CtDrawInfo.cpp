/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:          CtDrawInfo
*/


#include "CtDrawInfo.h"
#include "CtLanguage.h"
#include "string_api.h"
#include "CtMemory.h"
#include "CtDraw.h"
#include "CtDrawCache.h"

//#define DEBUG_PRINT	1
//#define USE_PATH_CACHE	1

CtFontSet::CtFontSet()
{
	ctor();
}

CtFontSet::CtFontSet(const CtColor& _color)
{
	ctor();
	setColor(_color);
}

CtFontSet::CtFontSet(FontSetType _type)
{
	ctor();
	setFontAttribute(_type);
}

CtFontSet::CtFontSet(FontSetType _type, const CtColor& _fontColor)
{
	ctor();
	setFontAttribute(_type);
	setColor(_fontColor);
}

CtFontSet::CtFontSet(FontSetType _type, const CtColor& _fontColor, const CtColor& _edgeColor)
{
	ctor();
	setFontAttribute(_type);
	setColor(_fontColor, _edgeColor);
}

CtFontSet::~CtFontSet()
{
}

void CtFontSet::ctor()
{
	memset(&fontStyle, 0, sizeof(fontStyle));
	fontStyle.font_size = 0;
	fontStyle.locale = LOCALE_NONE;
	fontStyle.aspect_ratio = ASPECT_RATIO_DEFAULT;
	fontStyle.auto_adjust = AUTO_ADJUST_ENABLE;
	fontStyle.attr = FONT_ATTRIBUTE_NORMAL;
	fontStyle.halign = HALIGN_LEFT;
	fontStyle.valign = VALIGN_DEFAULT;
	fontStyle.isWriteOneChar = false;
	fontColor = CtColor::Black;
	edgeColor = CtColor::NoColor;
	strokeWidth = -1;
	languageID = LANGUAGE_ID_NONE;
}

bool CtFontSet::setSize(short _size)
{
	if (_size < 0)
		return false;
	
	if (fontStyle.font_size == (unsigned char)_size) {
		return false;
	}
	
	fontStyle.font_size = (unsigned char)_size;
	if( _size == 0 ){
		fontStyle.auto_adjust = AUTO_ADJUST_ENABLE;
	} else {
		fontStyle.auto_adjust = AUTO_ADJUST_DISABLE;
	}
	return true;
}

bool CtFontSet::getStringSize(CtSize& Size, const char* _pstr)
{
	bool bRet = false;
	
	unsigned short width, height;
	unsigned short* p;
	int len = get_char_string_length(_pstr);

	if (len == 0)
		return bRet;
	
	if ((p = (unsigned short*)operator new(sizeof(*p) * (len +1))) == NULL) {
		return bRet;
	}

	convert_char_str_to_ushort_str(p, _pstr);
	
	if (GDI_GetDrawRect(&fontStyle, p, &width, &height) == GDI_NO_ERROR) {
		Size.width = width;
		Size.height = height;
		bRet = true;
	}

	operator delete(p);
	return bRet;
}

bool CtFontSet::getStringSize(CtSize& Size, const unsigned short* _pstr)
{
	unsigned short width, height;

	if (_pstr == NULL)
		return false;
	
	if (GDI_GetDrawRect(&fontStyle, (unsigned short*)_pstr, &width, &height) == GDI_NO_ERROR) {
		Size.width = width;
		Size.height = height;
		return true;
	}
	return false;
}

bool CtFontSet::getStringSize(CtSize& Size, GDI_STRING_ID _id)
{
	unsigned short width, height;
	unsigned short* p;
	
	p = GDI_GetString(languageID, _id);
	
	if (GDI_GetDrawRect(&fontStyle, p, &width, &height) == GDI_NO_ERROR) {
		Size.width = width;
		Size.height = height;
		return true;
	}
	return false;
}

bool CtFontSet::setColor(const CtColor& _fontColor, const CtColor& _edgeColor)
{
	fontColor = _fontColor;
	edgeColor = _edgeColor;
	return true;
}

bool CtFontSet::setColor(const CtColor& _fontColor)
{
	if (fontColor != _fontColor) {
		fontColor = _fontColor;
		return true;
	}
	return false;
}

bool CtFontSet::setStrokeWidth(short _stroke_width)
{
	if (strokeWidth != _stroke_width) {
		strokeWidth = _stroke_width;
		return true;
	}
	return false;
}


bool CtFontSet::setEdgeColor(CtColor& _edgeColor)
{
	edgeColor = _edgeColor;
	return true;
}

bool CtFontSet::setFontAttribute(FontSetType _type)
{
	bool bRet = false;
	FONT_ATTRIBUTE type = (FONT_ATTRIBUTE)(_type & CT_FONT_TYPE_MASK);
	HALIGN halign;
	VALIGN valign;

	switch (_type) {
	case FontTypeNormal_alignAuto:
	case FontTypeBold_alignAuto:
	case FontTypeOutline_alignAuto:
	case FontTypeMono_alignAuto:
		halign = HALIGN_LEFT;
		valign = VALIGN_DEFAULT;
		break;
	default:
		switch (_type & CT_FONT_ALIGN_MASK) {
		case CT_FONT_ALIGN_LEFT:
			halign = HALIGN_LEFT;
			break;
		case CT_FONT_ALIGN_CENTER:
			halign = HALIGN_CENTER;
			break;
		case CT_FONT_ALIGN_RIGHT:
			halign = HALIGN_RIGHT;
			break;
		default:
			halign = HALIGN_CENTER;
			break;
		}

		switch (_type & CT_FONT_VALIGN_MASK) {
		case CT_FONT_VALIGN_TOP:
			valign = VALIGN_TOP;
			break;
		case CT_FONT_VALIGN_MIDDLE:
			valign = VALIGN_MIDDLE;
			break;
		case CT_FONT_VALIGN_BOTTOM:
			valign = VALIGN_BOTTOM;
			break;
		default:
			valign = VALIGN_DEFAULT;
			break;
		}
		break;
	}
	
	if (fontStyle.attr != type) {
		fontStyle.attr = type;
		bRet = true;
	}

	if (fontStyle.halign != halign) {
		fontStyle.halign = halign;
		bRet = true;
	}

	if (fontStyle.valign != valign) {
		fontStyle.valign = valign;
		bRet = true;
	}
	
	return bRet;
}

bool CtFontSet::setAlign(CtAlign _align)
{
	HALIGN	halign = fontStyle.halign;
	VALIGN	valign = fontStyle.valign;

	if (_align == AlignInvalid)
		return false;
	
	switch (_align & AlignHMask) {
	case AlignLeft:		halign = HALIGN_LEFT;		break;
	case AlignHCenter:	halign = HALIGN_CENTER;		break;
	case AlignRight:	halign = HALIGN_RIGHT;		break;
	default:		break;
	}

	switch (_align & AlignVMask) {
	case AlignTop:		valign = VALIGN_TOP;		break;
	case AlignVCenter:	valign = VALIGN_MIDDLE;		break;
	case AlignBottom:	valign = VALIGN_BOTTOM;		break;
	default:		break;
	}

	if ((fontStyle.halign == halign) && (fontStyle.valign == valign))
		return false;

	fontStyle.halign = halign;
	fontStyle.valign = valign;
	
	return true;
}

bool CtFontSet::setLocale(FONT_LOCALE _locale)
{
	if (fontStyle.locale == LOCALE_FX)
		return false;

	if (fontStyle.locale == _locale)
		return false;

	fontStyle.locale = _locale;
	return true;
}

bool CtFontSet::setLanguageId(LANGUAGE_ID _language)
{
	if (languageID == _language)
		return false;
	
	languageID = _language;
	setLocale(CtLanguage::getLocale(languageID));
	return true;
}

LANGUAGE_ID CtFontSet::getLanguageId()
{
	return languageID;
}

bool CtFontSet::setAspectRatio(CtAspectRatio _ratio)
{
	ASPECT_RATIO ratio = fontStyle.aspect_ratio;
	
	switch (_ratio) {
	case AspectRatio_Default:	ratio = ASPECT_RATIO_DEFAULT;	break;
	case AspectRatio_Original:	ratio = ASPECT_RATIO_DEFAULT;	break;
	case AspectRatio_Same:		ratio = ASPECT_RATIO_SAME;		break;
	case AspectRatio_Wide:		ratio = ASPECT_RATIO_WIDE;		break;
	case AspectRatio_Narrow:	ratio = ASPECT_RATIO_NARROW;	break;
	case AspectRatio_Special:	ratio = ASPECT_RATIO_DEFAULT;	break;
	default:		break;
	}
	
	if (fontStyle.aspect_ratio == ratio)
		return false;
	
	fontStyle.aspect_ratio = ratio;
	return true;
}

bool CtFontSet::setAutoAdjust(bool _adjust)
{
	AUTO_ADJUST  adjust = fontStyle.auto_adjust;

	if (_adjust == true) {
		adjust = AUTO_ADJUST_ENABLE;
	} else {
		adjust = AUTO_ADJUST_DISABLE;
	}

	if (fontStyle.auto_adjust == adjust)
		return false;
	
	fontStyle.auto_adjust = adjust;
	return true;
}

bool CtFontSet::setFontSet(const CtFontSet &_fontset)
{
	bool bRet = false;

	if (isSame(_fontset) == false) {
		fontColor = _fontset.fontColor;
		edgeColor = _fontset.edgeColor;
		strokeWidth = _fontset.strokeWidth;
		languageID= _fontset.languageID;
		fontStyle = _fontset.fontStyle;
		bRet = true;
	}
	return bRet;
}

bool CtFontSet::isSame(const CtFontSet& _fontset)
{
	if ((fontColor == _fontset.fontColor) &&
		(edgeColor == _fontset.edgeColor) &&
		(strokeWidth == _fontset.strokeWidth) &&
		(fontStyle.font_size == _fontset.fontStyle.font_size) &&
		(fontStyle.locale == _fontset.fontStyle.locale) &&
		(fontStyle.aspect_ratio == _fontset.fontStyle.aspect_ratio) &&
		(fontStyle.auto_adjust == _fontset.fontStyle.auto_adjust) &&
		(fontStyle.attr == _fontset.fontStyle.attr) &&
		(fontStyle.halign == _fontset.fontStyle.halign) &&
		(fontStyle.valign == _fontset.fontStyle.valign) &&
		(fontStyle.isWriteOneChar == _fontset.fontStyle.isWriteOneChar) &&
		(languageID == _fontset.languageID)) {
		return true;
	}
	return false;
}

CtFontSet& CtFontSet::operator=(const CtFontSet &_fontset)
{
	setFontSet(_fontset);
	return *this;
}


const unsigned long CtDrawInfo::m_CrcTable[256] = { 
	0x00000000, 0x77073096, 0xee0e612c, 0x990951ba,
	0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
	0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
	0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
	0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de,
	0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
	0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,
	0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5,
	0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
	0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
	0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940,
	0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
	0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116,
	0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f,
	0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
	0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,
	0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a,
	0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
	0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818,
	0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
	0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
	0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457,
	0x65b0d9c6, 0x12b7e950, 0x8bbeb8ea, 0xfcb9887c,
	0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
	0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2,
	0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb,
	0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
	0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9,
	0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086,
	0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
	0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4,
	0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad,
	0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
	0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683,
	0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8,
	0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
	0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe,
	0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7,
	0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
	0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
	0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252,
	0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
	0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60,
	0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79,
	0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
	0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f,
	0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04,
	0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
	0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a,
	0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
	0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
	0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21,
	0x86d3d2d4, 0xf1d4e242, 0x68ddb3f8, 0x1fda836e,
	0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
	0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c,
	0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45,
	0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
	0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db,
	0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0,
	0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
	0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6,
	0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf,
	0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
	0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d,
};

const unsigned int CtDrawInfo::m_CrcTableNum = 256;

CtDrawInfo::CtDrawInfo() :
	m_Type(DrawType_None)
{
	setClassType(CtClassType_DrawInfo);

	m_Base.blend = GDI_BLEND_MODE_SRC;
	
	m_Base.clip_area.x = 0;
	m_Base.clip_area.y = 0;
	m_Base.clip_area.width = 0;
	m_Base.clip_area.height = 0;
	
	m_Base.draw_area.x = 0;
	m_Base.draw_area.y = 0;
	m_Base.draw_area.width = 0;
	m_Base.draw_area.height = 0;

	m_DrawImage = GDI_INVALID_ID;
	m_bFast = false;
}

CtDrawInfo::~CtDrawInfo()
{
	if (m_DrawImage != GDI_INVALID_ID) {
		CtDrawCache::getInstance()->unreferCache(*this);
		m_DrawImage = GDI_INVALID_ID;
	}
}

bool CtDrawInfo::setColor(GDI_COLOR* pGdiColor, const CtColor& Color)
{
	if (pGdiColor == NULL)
		return false;
	
	switch (Color.Type) {
	case ColorNone:
		if (pGdiColor->type == 0) {	/* pgr0838 */
			return false;
		}
		pGdiColor->type = (VGPaintType)0;	/* pgr0838 */
		pGdiColor->color = 0;
		pGdiColor->gradient = NULL;
		return true;
	case ColorRGBA:
		if ((pGdiColor->type == VG_PAINT_TYPE_COLOR) &&
			(pGdiColor->color == Color.RGBA)) {
			return false;
		}
		pGdiColor->type = VG_PAINT_TYPE_COLOR;
		pGdiColor->color = Color.RGBA;
		pGdiColor->gradient = NULL;
		return true;
	case ColorGradient:
		if ((pGdiColor->type == VG_PAINT_TYPE_LINEAR_GRADIENT) &&
			(pGdiColor->gradient == (const GDI_GRADIENT*)Color.Gradient)) {
			return false;
		}
		pGdiColor->type = VG_PAINT_TYPE_LINEAR_GRADIENT;
		pGdiColor->color = 0;
		pGdiColor->gradient = (const GDI_GRADIENT*)Color.Gradient;
		return true;
	default:
		break;
	}
	return false;
}

CtColor CtDrawInfo::getColor(const GDI_COLOR* pGdiColor) const
{
	if (pGdiColor == NULL)
		return CtColor::NoColor;
	
	switch (pGdiColor->type) {
	case VG_PAINT_TYPE_COLOR:
		return CtColor(pGdiColor->color);
	case VG_PAINT_TYPE_LINEAR_GRADIENT:
		return CtColor((void*)&pGdiColor->gradient);
	default:
		return CtColor::NoColor;
	}
	return CtColor::NoColor;
}


bool CtDrawInfo::setAlign(CtAlign _align)
{
	return false;
}

bool CtDrawInfo::setAspectRatio(CtAspectRatio _ratio)
{
	return false;
}

bool CtDrawInfo::setAutoAdjust(bool _adjust)
{
	return false;
}

bool CtDrawInfo::isSame(GDI_COLOR* pGdiColor, const CtColor& Color)
{
	if (pGdiColor == NULL)
		return false;
	
	switch (Color.Type) {
	case ColorNone:
		if (pGdiColor->type == 0) {	/* pgr0838 */
			return true;
		}
		return false;
	case ColorRGBA:
		if ((pGdiColor->type == VG_PAINT_TYPE_COLOR) &&
			(pGdiColor->color == Color.RGBA)) {
			return true;
		}
		return false;
	case ColorGradient:
		if ((pGdiColor->type == VG_PAINT_TYPE_LINEAR_GRADIENT) &&
			(pGdiColor->gradient == (const GDI_GRADIENT*)Color.Gradient)) {
			return true;
		}
		return false;
	default:
		break;
	}
	return false;
}

bool CtDrawInfo::setRegion(const CtRegion& _region)
{
	return setRegion(_region.x, _region.y, _region.width, _region.height);
}

bool CtDrawInfo::setRegion(short _x, short _y, short _width, short _height)
{
	if ((_width < 0) || (_height < 0))
		return false;
	
	if ((m_Base.draw_area.x == _x) &&
		(m_Base.draw_area.y == _y) &&
		(m_Base.draw_area.width == _width) &&
		(m_Base.draw_area.height == _height)) {
		return false;
	}
	
	m_Base.draw_area.x = _x;
	m_Base.draw_area.y = _y;
	m_Base.draw_area.width = _width;
	m_Base.draw_area.height = _height;
	return true;
}

bool CtDrawInfo::getRegion(CtRegion& _region)
{
	if ((m_Base.draw_area.width <= 0) || (m_Base.draw_area.height <= 0)) {
		_region = NoRegion;
		return false;
	}
	_region.x = m_Base.draw_area.x;
	_region.y = m_Base.draw_area.y;
	_region.width = m_Base.draw_area.width;
	_region.height = m_Base.draw_area.height;
	return true;
}

bool CtDrawInfo::setClip(const CtRegion& _region)
{
	return setClip(_region.x, _region.y, _region.width, _region.height);
}

bool CtDrawInfo::setClip(short _x, short _y, short _width, short _height)
{
	if ((_width <= 0) || (_height <= 0))
		return false;

	GDI_REGION Result;
	GDI_REGION Draw = m_Base.draw_area;

	if ((m_Base.clip_area.x == _x) &&
		(m_Base.clip_area.y == _y) &&
		(m_Base.clip_area.width == _width) &&
		(m_Base.clip_area.height == _height)) {
		return false;
	}

	//x0の大きい方
	Result.x = (Draw.x > _x) ? Draw.x : _x;/* pgr0351 */
	//y0の大きい方
	Result.y = (Draw.y > _y) ? Draw.y : _y;/* pgr0351 */
	//x1の小さい方
	Result.width = ((Draw.x + Draw.width) < (_x + _width)) ? (Draw.x + Draw.width) - Result.x : (_x + _width) - Result.x;/* pgr0351 */
	if (Result.width < 0) Result.width = 0;
	//y1の小さい方
	Result.height = ((Draw.y + Draw.height) < (_y + _height)) ? (Draw.y + Draw.height) - Result.y : (_y + _height) - Result.y;/* pgr0351 */
	if (Result.height < 0) Result.height = 0;
		
	m_Base.clip_area = Result;
		
	return true;
}

bool CtDrawInfo::getClip(CtRegion& _clip)
{
	if ((m_Base.clip_area.width <= 0) || (m_Base.clip_area.height <= 0)) {
		_clip = NoRegion;
		return false;
	}
	_clip.x = m_Base.clip_area.x;
	_clip.y = m_Base.clip_area.y;
	_clip.width = m_Base.clip_area.width;
	_clip.height = m_Base.clip_area.height;
	return true;
}

bool CtDrawInfo::setPos(const CtPosition& _position)
{
	return setPos(_position.x, _position.y);
}

bool CtDrawInfo::setPos(short _x, short _y)
{
	if ((m_Base.draw_area.x == _x) &&
		(m_Base.draw_area.y == _y)) {
		return false;
	}
	
	m_Base.draw_area.x = _x;
	m_Base.draw_area.y = _y;
	m_Base.clip_area.x = _x;
	m_Base.clip_area.y = _y;
	
	return true;
}

bool CtDrawInfo::movePos(const CtPosition& _position)
{
	return movePos(_position.x, _position.y);
}

bool CtDrawInfo::movePos(short _x, short _y)
{
	m_Base.draw_area.x += _x;
	m_Base.draw_area.y += _y;
	m_Base.clip_area.x += _x;
	m_Base.clip_area.y += _y;
	
	return true;
}

bool CtDrawInfo::setTrans(bool bTrans)
{
	bool bRet = false;
	
	if (bTrans == true) {
		if (m_Base.blend != GDI_BLEND_MODE_SRC_OVER) {
			m_Base.blend = GDI_BLEND_MODE_SRC_OVER;
			bRet = true;
		}
	} else {
		if (m_Base.blend != GDI_BLEND_MODE_SRC) {
			m_Base.blend = GDI_BLEND_MODE_SRC;
			bRet = true;
		}
	}
	return bRet;
}

bool CtDrawInfo::isTrans() const
{
	if (m_Base.blend == GDI_BLEND_MODE_SRC_OVER)
		return true;

	return false;
}

bool CtDrawInfo::setColor(const CtColor& fillColor)
{
	return false;
}

bool CtDrawInfo::setColor(const CtColor& fillColor, const CtColor& edgeColor)
{
	return false;
}

CtColor CtDrawInfo::getFillColor() const
{
	return CtColor::NoColor;
}

CtColor CtDrawInfo::getEdgeColor() const
{
	return CtColor::NoColor;
}

bool CtDrawInfo::setDrawImage(GDI_HANDLER id)
{
	if (id == m_DrawImage)
		return false;
	
	if (m_DrawImage != GDI_INVALID_ID) {
		CtDrawCache::getInstance()->unreferCache(*this);
	}
	m_DrawImage = id;
	return true;
}

void CtDrawInfo::lostDrawImage()
{
	m_DrawImage = GDI_INVALID_ID;
}

bool CtDrawInfo::haveDrawImage() const
{
	if (m_DrawImage != GDI_INVALID_ID)
		return true;
	
	return false;
}

GDI_HANDLER CtDrawInfo::getDrawImage()
{
	return m_DrawImage;
}

bool CtDrawInfo::drawFast()
{
	if (m_DrawImage == GDI_INVALID_ID)
		return false;
	
	return CtDraw::getInstance()->draw(*this);
}

unsigned long CtDrawInfo::calcKey(unsigned long key1, unsigned long key2)
{
	return CtDrawInfo::calcCRC(key1, (unsigned char*)&key2, sizeof(key2));
}

unsigned long CtDrawInfo::calcCRC(unsigned long base, const unsigned char* data, unsigned int size)
{
	unsigned long crc = base;

	if (data == NULL)
		return 0;
	
	for (unsigned int i = 0; i < size; i++) {
		crc = m_CrcTable[(crc ^ data[i]) % m_CrcTableNum] ^ (crc >> 8);
	}
	return crc ^ ~0L;
}

unsigned long CtDrawInfo::getDrawKey()
{
	unsigned long crc = 0;
	struct calcTmp {
		short width;
		short height;
	};
	calcTmp Tmp;
	
	Tmp.width = m_Base.draw_area.width;
	Tmp.height = m_Base.draw_area.height;
	crc = calcCRC(0, (unsigned char*)&Tmp, sizeof(Tmp));
	
	return crc;
}

unsigned long CtDrawInfo::getPathKey()
{
	return 0;
}

void CtString::ctor()
{
	m_id = STRING_ID_INVALID;
	m_pCache = NULL;
	m_bufSize = 0;
	m_Type = DrawType_String;
	m_languageID = LANGUAGE_ID_NONE;
		
	setFontSet(CtFontSet());
	
	m_String.str = NULL;
	setColor(m_fontColor, m_edgeColor);
	setStrokeWidth(-1);
}

CtString::CtString()
{
	ctor();
}

CtString::CtString(const GDI_STRING_ID _id)
{
	ctor();
	setString(_id);
}

CtString::CtString(const GDI_STRING_ID _id, const CtFontSet& _fontset)
{
	ctor();
	setFontSet(_fontset);
	setColor(_fontset.fontColor, _fontset.edgeColor);
	setStrokeWidth(_fontset.strokeWidth);
	setString(_id);
}

CtString::CtString(const char* _pstr)
{
	ctor();
	setString(_pstr);
}

CtString::CtString(const char* _pstr, const CtFontSet& _fontset)
{
	ctor();
	setFontSet(_fontset);
	setColor(_fontset.fontColor, _fontset.edgeColor);
	setStrokeWidth(_fontset.strokeWidth);
	setString(_pstr);
}

CtString::CtString(const unsigned short* _pstr)
{
	ctor();
	setString(_pstr);
}

CtString::CtString(const unsigned short* _pstr, const CtFontSet& _fontset)
{
	ctor();
	setFontSet(_fontset);
	setColor(_fontset.fontColor, _fontset.edgeColor);
	setStrokeWidth(_fontset.strokeWidth);
	setString(_pstr);
}

CtString::~CtString()
{
	if (m_String.str != NULL) {
		operator delete(m_String.str);
	}
	if (m_pCache != NULL) {
#if USE_PATH_CACHE
		CtDrawCache::getInstance()->unreferCache(*this);
#else
		GDI_DeleteCache((GDI_CACHE_BASE*)m_pCache);
#endif
		m_pCache = NULL;
	}
}

bool CtString::setFontStyle(GDI_FONT_STYLE _fontStyle)
{
	if ((m_String.font_style.font_size == _fontStyle.font_size) &&
		(m_String.font_style.locale == _fontStyle.locale) &&
		(m_String.font_style.aspect_ratio == _fontStyle.aspect_ratio) &&
		(m_String.font_style.auto_adjust == _fontStyle.auto_adjust) &&
		(m_String.font_style.attr == _fontStyle.attr) &&
		(m_String.font_style.halign == _fontStyle.halign) &&
		(m_String.font_style.valign == _fontStyle.valign) &&
		(m_String.font_style.isWriteOneChar == _fontStyle.isWriteOneChar)) {
		return false;
	}
	memset(&m_String.font_style, 0, sizeof(m_String.font_style));
	m_String.font_style = _fontStyle;
	
	if (m_pCache != NULL) {
#if USE_PATH_CACHE
		CtDrawCache::getInstance()->unreferCache(*this);
#else
		GDI_DeleteCache((GDI_CACHE_BASE*)m_pCache);
#endif
		m_pCache = NULL;
	}
	return true;
}

bool CtString::setString(const GDI_STRING_ID _id, const CtFontSet& _fontset)
{
	setFontSet(_fontset);

	return setString(_id);
}

bool CtString::setString(const GDI_STRING_ID _id)
{
	if (m_id != _id) {
		m_id = _id;
	}
	if (m_languageID == LANGUAGE_ID_NONE) {
		setLanguageId(CtLanguage::getLanguageID(_id));
	}

	return setString(GDI_GetString(m_languageID, _id),false);
}

bool CtString::setString(const char* _pstr, const CtFontSet& _fontset)
{
	setFontSet(_fontset);
    
	return setString(_pstr);
}

bool CtString::setString(const char* _pstr)
{
	bool bSameCheck = false;
	int len = 0;
	unsigned short* p = NULL;

	m_id = STRING_ID_INVALID;	// 初期値に戻す

	if ((_pstr == NULL) || (_pstr[0] == 0) || ((len = get_char_string_length(_pstr)) <= 0)) {/* parasoft-suppress BD-PB-NOTINIT */
		if (m_String.str == NULL) return false;
		
		operator delete(m_String.str);
		m_String.str = NULL;
		goto cache_clear;
	}

	unsigned int newBufSize = sizeof(*p) * (len +1);
	if (m_String.str != NULL) {
		if (len == get_ushort_string_length(m_String.str)) {	// 同じ文字列長なら新旧比較
			bSameCheck = true;
		} else if (newBufSize < m_bufSize) {					// 短ければバッファを流用
			p = m_String.str;
		} else {												// 長ければ旧バッファ削除
			operator delete(m_String.str);
			m_String.str = NULL;
		}
	}
	if (p == NULL) {
		if ((p = (unsigned short*)operator new(newBufSize)) == NULL)
			goto cache_clear;
		m_bufSize = newBufSize;		/* pgr0351 */
	}
	//convert_char_str_to_ushort_str(p, _pstr);
	convert_sjis_to_utf16(_pstr, p);
	if (bSameCheck == true) {
		if (memcmp(m_String.str, p, newBufSize) == 0) {
			operator delete(p);
			return false;
		} else {
			operator delete(m_String.str);
		}
	}
	m_String.str = p;

  cache_clear:
	if (m_pCache != NULL) {
#if USE_PATH_CACHE
		CtDrawCache::getInstance()->unreferCache(*this);
#else
		GDI_DeleteCache((GDI_CACHE_BASE*)m_pCache);
#endif
		m_pCache = NULL;
	}
	
	return true;
}

bool CtString::setString(const unsigned short* _pstr, const CtFontSet& _fontset)
{
	setFontSet(_fontset);
		
	return setString(_pstr);
}

bool CtString::setString(const unsigned short* _pstr, bool bChangeid)
{
	bool bSameCheck = false;
	int len = 0;
	unsigned short *p = NULL;

	if (bChangeid)
		m_id = STRING_ID_INVALID;	// 初期値に戻す

	if ((_pstr == NULL) || (_pstr[0] == 0) || ((len = get_ushort_string_length(_pstr)) <= 0)) {
		if (m_String.str == NULL) return false;
		
		operator delete(m_String.str);
		m_String.str = NULL;
		goto cache_clear;
	}

	unsigned int newBufSize = sizeof(*p) * (len +1);
	if (m_String.str != NULL) {
		if (len == get_ushort_string_length(m_String.str)) {	// 同じ文字列長なら新旧比較
			bSameCheck = true;
		} else if (newBufSize < m_bufSize) {					// 短ければバッファを流用
			p = m_String.str;
		} else {												// 長ければ旧バッファ削除
			operator delete(m_String.str);
			m_String.str = NULL;
		}
	}
	if (p == NULL) {
		if ((p = (unsigned short*)operator new(newBufSize)) == NULL)
			goto cache_clear;
		m_bufSize = newBufSize;		/* pgr0351 */
	}
	memcpy(p, _pstr, newBufSize - sizeof(*p));
	p[len] = 0x0000;
	if (bSameCheck == true) {
		if (memcmp(m_String.str, p, newBufSize) == 0) {
			operator delete(p);
			return false;
		} else {
			operator delete(m_String.str);
		}
	}
	m_String.str = p;

  cache_clear:
	if (m_pCache != NULL) {
#if USE_PATH_CACHE
		CtDrawCache::getInstance()->unreferCache(*this);
#else
		GDI_DeleteCache((GDI_CACHE_BASE*)m_pCache);
#endif
		m_pCache = NULL;
	}

	return true;
}

unsigned short* CtString::getString()
{
	return m_String.str;
}

CtRegion CtString::getRect()
{
	return CtRegion();
}

bool CtString::updeteLanguage()
{
	if (m_id == STRING_ID_INVALID)
		return false;
	
	setLanguageId(CtLanguage::getLanguageID(m_id));
	setLocale(CtLanguage::getLocale(m_languageID));

	return setString(m_id);
}

bool CtString::setFontSet(const CtFontSet& _fontset)
{
	bool bRet = false;

	if (m_fontColor != _fontset.fontColor) {
		m_fontColor = _fontset.fontColor;
		bRet = true;
	}
	if (m_edgeColor != _fontset.edgeColor) {
		m_edgeColor = _fontset.edgeColor;
		bRet = true;
	}		
	if (m_StrokeWidth != _fontset.strokeWidth) {					/* parasoft-suppress BD-PB-NOTINIT */
		m_StrokeWidth = _fontset.strokeWidth;
		bRet = true;
	}
	
	if (setFontStyle(_fontset.fontStyle) == true)
		bRet = true;
	
	if (setColor(_fontset.fontColor, _fontset.edgeColor) == true)
		bRet = true;

	if (setStrokeWidth(_fontset.strokeWidth) == true)
		bRet = true;

	if (setLanguageId(_fontset.languageID) == true)
		bRet = true;

	if ((bRet == true) && (m_pCache != NULL)) {
#if USE_PATH_CACHE
		CtDrawCache::getInstance()->unreferCache(*this);
#else
		GDI_DeleteCache((GDI_CACHE_BASE*)m_pCache);
#endif
		m_pCache = NULL;
	}
	
	return bRet;
}

bool CtString::setSize(short _size)
{
	if (m_String.font_style.font_size == (unsigned short)_size) {
		return false;
	}
	
	m_String.font_style.font_size = (unsigned char)_size;	/* pgr0360  符号合わせてます！何いってんの？ */
	if( _size == 0 ){
		m_String.font_style.auto_adjust = AUTO_ADJUST_ENABLE;
	} else {
		m_String.font_style.auto_adjust = AUTO_ADJUST_DISABLE;
	}
	
	if (m_pCache != NULL) {
#if USE_PATH_CACHE
		CtDrawCache::getInstance()->unreferCache(*this);
#else
		GDI_DeleteCache((GDI_CACHE_BASE*)m_pCache);
#endif
		m_pCache = NULL;
	}
	return true;
}

bool CtString::setFontAttribute(FontSetType _type)
{
	bool bRet = false;
	FONT_ATTRIBUTE type = (FONT_ATTRIBUTE)(_type & CT_FONT_TYPE_MASK);
	HALIGN halign;
	VALIGN valign;

	switch (_type) {
	case FontTypeNormal_alignAuto:
	case FontTypeBold_alignAuto:
	case FontTypeOutline_alignAuto:
	case FontTypeMono_alignAuto:
		halign = HALIGN_LEFT;
		valign = VALIGN_DEFAULT;
		break;
	default:
		switch (_type & CT_FONT_ALIGN_MASK) {
		case CT_FONT_ALIGN_LEFT:
			halign = HALIGN_LEFT;
			break;
		case CT_FONT_ALIGN_CENTER:
			halign = HALIGN_CENTER;
			break;
		case CT_FONT_ALIGN_RIGHT:
			halign = HALIGN_RIGHT;
			break;
		default:
			halign = HALIGN_CENTER;
			break;
		}

		switch (_type & CT_FONT_VALIGN_MASK) {
		case CT_FONT_VALIGN_TOP:
			valign = VALIGN_TOP;
			break;
		case CT_FONT_VALIGN_MIDDLE:
			valign = VALIGN_MIDDLE;
			break;
		case CT_FONT_VALIGN_BOTTOM:
			valign = VALIGN_BOTTOM;
			break;
		default:
			valign = VALIGN_DEFAULT;
			break;
		}
	}
		

	if (m_String.font_style.attr != type) {
		m_String.font_style.attr = type;
		bRet = true;
	}

	if (m_String.font_style.halign != halign) {
		m_String.font_style.halign = halign;
		bRet = true;
	}

	if (m_String.font_style.valign != valign) {
		m_String.font_style.valign = valign;
		bRet = true;
	}
	
	if ((bRet == true) && (m_pCache != NULL)) {
#if USE_PATH_CACHE
		CtDrawCache::getInstance()->unreferCache(*this);
#else
		GDI_DeleteCache((GDI_CACHE_BASE*)m_pCache);
#endif
		m_pCache = NULL;
	}
	return bRet;
}

bool CtString::setAlign(CtAlign _align)
{
	HALIGN halign = m_String.font_style.halign;
	VALIGN valign = m_String.font_style.valign;

	if (_align == AlignInvalid)
		return false;

	switch (_align & AlignHMask) {
	case AlignLeft:		halign = HALIGN_LEFT;		break;
	case AlignHCenter:	halign = HALIGN_CENTER;		break;
	case AlignRight:	halign = HALIGN_RIGHT;		break;
	default:		break;
	}

	switch (_align & AlignVMask) {
	case AlignTop:		valign = VALIGN_TOP;		break;
	case AlignVCenter:	valign = VALIGN_MIDDLE;		break;
	case AlignBottom:	valign = VALIGN_BOTTOM;		break;
	default:		break;
	}

	if ((m_String.font_style.halign == halign) && (m_String.font_style.valign == valign))
		return false;

	m_String.font_style.halign = halign;
	m_String.font_style.valign = valign;
	
	if (m_pCache != NULL) {
#if USE_PATH_CACHE
		CtDrawCache::getInstance()->unreferCache(*this);
#else
		GDI_DeleteCache((GDI_CACHE_BASE*)m_pCache);
#endif
		m_pCache = NULL;
	}
	return true;
}

bool CtString::setLocale(FONT_LOCALE _locale)
{
	if (m_String.font_style.locale == LOCALE_FX)
		return false;

	if (m_String.font_style.locale == _locale)
		return false;

	m_String.font_style.locale = _locale;
	
	if (m_pCache != NULL) {
#if USE_PATH_CACHE
		CtDrawCache::getInstance()->unreferCache(*this);
#else
		GDI_DeleteCache((GDI_CACHE_BASE*)m_pCache);
#endif
		m_pCache = NULL;
	}
	return true;
}

bool CtString::setLanguageId(LANGUAGE_ID _language)
{
	if (m_languageID == _language)
		return false;
	
	m_languageID = _language;
	
	setLocale(CtLanguage::getLocale(m_languageID));
	
	if (m_pCache != NULL) {
#if USE_PATH_CACHE
		CtDrawCache::getInstance()->unreferCache(*this);
#else
		GDI_DeleteCache((GDI_CACHE_BASE*)m_pCache);
#endif
		m_pCache = NULL;
	}
	return true;
}

bool CtString::setAspectRatio(CtAspectRatio _ratio)
{
	ASPECT_RATIO ratio = m_String.font_style.aspect_ratio;

	switch (_ratio) {
	case AspectRatio_Default:	ratio = ASPECT_RATIO_DEFAULT;	break;
	case AspectRatio_Original:	ratio = ASPECT_RATIO_DEFAULT;	break;
	case AspectRatio_Same:		ratio = ASPECT_RATIO_SAME;		break;
	case AspectRatio_Wide:		ratio = ASPECT_RATIO_WIDE;		break;
	case AspectRatio_Narrow:	ratio = ASPECT_RATIO_NARROW;	break;
	case AspectRatio_Special:	ratio = ASPECT_RATIO_DEFAULT;	break;
	default:		break;
	}
	
	if (m_String.font_style.aspect_ratio == ratio)
		return false;
	
	m_String.font_style.aspect_ratio = ratio;

	if (m_pCache != NULL) {
#if USE_PATH_CACHE
		CtDrawCache::getInstance()->unreferCache(*this);
#else
		GDI_DeleteCache((GDI_CACHE_BASE*)m_pCache);
#endif
		m_pCache = NULL;
	}
	return true;
}

bool CtString::setAutoAdjust(bool _adjust)
{
	AUTO_ADJUST  adjust = m_String.font_style.auto_adjust;

	if (_adjust == true) {
		adjust = AUTO_ADJUST_ENABLE;
	} else {
		adjust = AUTO_ADJUST_DISABLE;
	}

	if (m_String.font_style.auto_adjust == adjust)
		return false;
	
	m_String.font_style.auto_adjust = adjust;
	
	if (m_pCache != NULL) {
#if USE_PATH_CACHE
		CtDrawCache::getInstance()->unreferCache(*this);
#else
		GDI_DeleteCache((GDI_CACHE_BASE*)m_pCache);
#endif
		m_pCache = NULL;
	}
	return true;
}

bool CtString::setColor(const CtColor& _fontcolor)
{
	bool bRet = false;
	CtColor fontcolor;

	if (_fontcolor.Type == ColorNone)
		fontcolor = m_fontColor;
	else
		fontcolor = _fontcolor;

	return CtDrawInfo::setColor(&m_String.fill_color, fontcolor);
}

bool CtString::setColor(const CtColor& _fontcolor, const CtColor& _edgecolor)
{
	bool bRet = false;
	CtColor fontcolor, edgecolor;

	if (_fontcolor.Type == ColorNone)
		fontcolor = m_fontColor;
	else
		fontcolor = _fontcolor;

	if (_edgecolor.Type == ColorNone)
		edgecolor = m_edgeColor;
	else
		edgecolor = _edgecolor;
	
	if (CtDrawInfo::setColor(&m_String.fill_color, fontcolor) == true)
		bRet = true;
	
	if (CtDrawInfo::setColor(&m_String.stroke_color, edgecolor) == true)
		bRet = true;
	
	return bRet;
}

bool CtString::setStrokeWidth(short _stroke_width)
{
	if (m_String.stroke_width != _stroke_width) {
		m_String.stroke_width = _stroke_width;
		return true;
	}
	return false;
}

CtColor CtString::getFillColor() const
{
	return CtDrawInfo::getColor(&m_String.fill_color);
}

CtColor CtString::getEdgeColor() const
{
	return CtDrawInfo::getColor(&m_String.stroke_color);
}


bool CtString::draw()
{
	if ((m_String.str == NULL) || (m_String.str[0] == 0))
		return false;

	if (CtDrawInfo::drawFast() == true)
		return true;
	
	if (m_String.font_style.locale == LOCALE_NONE) {
		setLocale(LOCALE_EN);
	}

	if (m_pCache == NULL) {
#if USE_PATH_CACHE
		m_pCache = CtDrawCache::getInstance()->referCache(*this);
#else
		m_pCache = GDI_CreateCacheFont(&m_String.font_style, m_String.str);
#endif
	}
	
	return CtDraw::getInstance()->draw(*this);
}

unsigned long CtString::getDrawKey()
{
	static const unsigned short dummyStr[] = {'N', 'o', ' ', 'S', 't', 'r', 'i', 'n', 'g', '\0'};
	const unsigned short* str = NULL;
	unsigned long crc = 0;
	struct calcTmp {
		GDI_FONT_STYLE	style;
		CtColor			fColor;
		CtColor			eColor;
		short			width;
	};
	
	if (m_String.str == NULL) {
		str = dummyStr;
	} else {
		str = m_String.str;
	}
	
	GDI_FONT_STYLE style = m_String.font_style;
	int length = get_ushort_string_length(str);
	
	calcTmp Tmp;
	memset(&Tmp, 0, sizeof(Tmp));
	Tmp.style = m_String.font_style;
	Tmp.style.locale = LOCALE_EN;
	Tmp.fColor = m_fontColor;
	Tmp.eColor = m_edgeColor;
	Tmp.width = m_StrokeWidth;

	crc = CtDrawInfo::getDrawKey();
	crc = calcCRC(crc, (unsigned char*)&Tmp, sizeof(Tmp));
	crc = calcCRC(crc, (unsigned char*)str, length * (sizeof *str));
	
#if DEBUG_PRINT
	CtDebugPrint(CtDbg, "** Type:%16s Cacheid:%p, size:%3d -> %08x\n", "String", this, sizeof(*this), crc);
#endif	
	
	return crc;
}

unsigned long CtString::getPathKey()
{
	static const unsigned short dummyStr[] = {'N', 'o', ' ', 'S', 't', 'r', 'i', 'n', 'g', '\0'};
	const unsigned short* str = NULL;
	unsigned long crc = 0;

	if (m_String.str == NULL) {
		str = dummyStr;
	} else {
		str = m_String.str;
	}
	GDI_FONT_STYLE style;
	int length = get_ushort_string_length(str);

	memset(&style, 0, sizeof(style));	// 0埋めしておかないと、ノイズが入ります
	style = m_String.font_style;
	
	crc = calcCRC(crc, (unsigned char*)&style, sizeof(style));
	crc = calcCRC(crc, (unsigned char*)str, length * (sizeof *str));
	
#if DEBUG_PRINT
	CtDebugPrint(CtDbg, "** Type:%16s Cacheid:%p, size:%3d -> %08x\n", "String", this, sizeof(*this), crc);
#endif	
	return crc;
}

void CtString::lostCache()
{
	if (m_pCache != NULL) {
		m_pCache = NULL;
	}
}


CtDrawable::CtDrawable()
{
	m_Type = DrawType_Drawable;
	m_Draw.drawable = GDI_INVALID_ID;
	
	m_Draw.image_style.aspect_ratio = ASPECT_RATIO_DEFAULT;
	m_Draw.image_style.auto_adjust = AUTO_ADJUST_ENABLE;
	m_Draw.image_style.halign = HALIGN_CENTER;
	m_Draw.image_style.valign = VALIGN_MIDDLE;
}

CtDrawable::CtDrawable(const GDI_HANDLER _id)
{
	m_Type = DrawType_Drawable;
	setDrawable(_id);
}

bool CtDrawable::setDrawable(const GDI_HANDLER _id)
{
	if (m_Draw.drawable == _id)							/* parasoft-suppress BD-PB-NOTINIT */
		return false;
	
	m_Draw.drawable = _id;
	return true;
}

bool CtDrawable::setAlign(CtAlign _align)
{
	HALIGN	halign = m_Draw.image_style.halign;
	VALIGN	valign = m_Draw.image_style.valign;


	switch (_align & AlignHMask) {
	case AlignLeft:		halign = HALIGN_LEFT;		break;
	case AlignHCenter:	halign = HALIGN_CENTER;		break;
	case AlignRight:	halign = HALIGN_RIGHT;		break;
	default:		break;
	}

	switch (_align & AlignVMask) {
	case AlignTop:		valign = VALIGN_TOP;		break;
	case AlignVCenter:	valign = VALIGN_MIDDLE;		break;
	case AlignBottom:	valign = VALIGN_BOTTOM;		break;
	default:		break;
	}

	if ((m_Draw.image_style.halign == halign) && (m_Draw.image_style.valign == valign))
		return false;

	m_Draw.image_style.halign = halign;
	m_Draw.image_style.valign = valign;
	
	return true;
}

bool CtDrawable::setAspectRatio(CtAspectRatio _ratio)
{
	ASPECT_RATIO ratio = m_Draw.image_style.aspect_ratio;
	
	switch (_ratio) {
	case AspectRatio_Default:	ratio = ASPECT_RATIO_DEFAULT;	break;
	case AspectRatio_Original:	ratio = ASPECT_RATIO_SAME;		break;
	case AspectRatio_Same:		ratio = ASPECT_RATIO_SAME;		break;
	case AspectRatio_Wide:		ratio = ASPECT_RATIO_WIDE;		break;
	case AspectRatio_Narrow:	ratio = ASPECT_RATIO_NARROW;	break;
	case AspectRatio_Special:	ratio = ASPECT_RATIO_DEFAULT;	break;
	default:		break;
	}
	
	if (m_Draw.image_style.aspect_ratio == ratio)
		return false;
	
	m_Draw.image_style.aspect_ratio = ratio;
	return true;
}

bool CtDrawable::setAutoAdjust(bool _adjust)
{
	AUTO_ADJUST  adjust = m_Draw.image_style.auto_adjust;

	if (_adjust == true) {
		adjust = AUTO_ADJUST_ENABLE;
	} else {
		adjust = AUTO_ADJUST_DISABLE;
	}

	if (m_Draw.image_style.auto_adjust == adjust)
		return false;
	
	m_Draw.image_style.auto_adjust = adjust;
	return true;
}

bool CtDrawable::draw()
{
	if (m_Draw.drawable == GDI_INVALID_ID)
		return false;
	
	return CtDraw::getInstance()->draw(*this);
}

unsigned long CtDrawable::getDrawKey()
{
	unsigned long crc = 0;

	crc = CtDrawInfo::getDrawKey();
	crc = calcCRC(crc, (unsigned char*)m_Draw.drawable, sizeof(m_Draw.drawable));
	
#if DEBUG_PRINT
	CtDebugPrint(CtDbg, "** Type:%16s Cacheid:%p, size:%3d -> %08x\n", "Drawable", this, size, crc);
#endif
	return crc;
}

void CtFill::ctor()
{
	m_Type = DrawType_Fill;
	CtDrawInfo::setColor(&m_Color, CtColor::NoColor);
}

CtFill::CtFill()
{
	ctor();
}

CtFill::CtFill(const CtColor& _color)
{
	ctor();
	setFill(_color);
}

CtFill::CtFill(const CtRegion& _region, const CtColor& _color)
{
	ctor();
	setFill(_region, _color);
}

bool CtFill::setFill(const CtColor& _color)
{
	bool bRet = false;

	if (CtDrawInfo::setColor(&m_Color, _color) == true)
		bRet = true;
	
	return bRet;
}

bool CtFill::setFill(const CtRegion& _region, const CtColor& _color)
{
	bool bRet = false;

	if (CtDrawInfo::setRegion(_region) == true)
		bRet = true;
	
	if (CtDrawInfo::setColor(&m_Color, _color) == true)
		bRet = true;
	
	return bRet;
}

bool CtFill::setColor(const CtColor& _fillColor)
{
	return CtDrawInfo::setColor(&m_Color, _fillColor);
}

CtColor CtFill::getFillColor() const
{
	return CtDrawInfo::getColor(&m_Color);
}

bool CtFill::draw()
{
	return CtDraw::getInstance()->draw(*this);
}

bool CtFill::drawFast()
{
	setTrans(false);

	return CtDraw::getInstance()->draw(*this);
}

unsigned long CtFill::getDrawKey()
{
	unsigned long crc = 0;

	crc = CtDrawInfo::getDrawKey();
	crc = calcCRC(crc, (unsigned char*)&m_Color, sizeof(m_Color));
	
	return crc;
}

void CtSVG::ctor()
{
	m_Type = DrawType_SVG;
		
	m_id = IMAGE_ID_INVALID;
	m_Draw.svg = NULL;
	m_Draw.image_style.aspect_ratio = ASPECT_RATIO_DEFAULT;
	m_Draw.image_style.auto_adjust = AUTO_ADJUST_ENABLE;
	m_Draw.image_style.halign = HALIGN_CENTER;
	m_Draw.image_style.valign = VALIGN_MIDDLE;
	
	m_pCache = NULL;
	setColor(CtColor::NoColor, CtColor::NoColor);
	m_fillColor = CtColor::NoColor;
	m_edgeColor = CtColor::NoColor;
}

CtSVG::CtSVG()
{
	ctor();
}

CtSVG::CtSVG(const GDI_IMAGE_ID _id, const CtColor& _fillColor, const CtColor& _edgeColor)
{
	ctor();
	setSVG(_id, _fillColor, _edgeColor);
}

CtSVG::~CtSVG()
{
	if (m_pCache != NULL) {
#if USE_PATH_CACHE
		CtDrawCache::getInstance()->unreferCache(*this);
#else
		GDI_DeleteCache((GDI_CACHE_BASE*)m_pCache);
#endif
		m_pCache = NULL;
	}
}

bool CtSVG::setSVG(const GDI_IMAGE_ID _id, const CtColor& _fillColor, const CtColor& _edgeColor)
{
	if (m_id == _id)
		return false;
	
	m_id = _id;
	m_Draw.svg = GDI_GetImageSVG(_id);
	m_fillColor = _fillColor;
	m_edgeColor = _edgeColor;
	setColor(_fillColor, _edgeColor);
		
	if (m_pCache != NULL) {
#if USE_PATH_CACHE
		CtDrawCache::getInstance()->unreferCache(*this);
#else
		GDI_DeleteCache((GDI_CACHE_BASE*)m_pCache);
#endif
		m_pCache = NULL;
	}
	return true;
}

GDI_IMAGE_SVG* CtSVG::getSVG()
{
	return m_Draw.svg;
}


bool CtSVG::setColor(const CtColor& _fill_color)
{
	bool bRet = false;
	CtColor fillColor = _fill_color;

	if (_fill_color.Type == ColorNone) {
		fillColor = m_fillColor;
	}
	
	if (CtDrawInfo::setColor(&m_Draw.fill, fillColor) == true) {
		bRet = true;
	}
	
	return bRet;
}

bool CtSVG::setColor(const CtColor& _fill_color, const CtColor& _edge_color)
{
	bool bRet = false;
	CtColor fillColor = _fill_color;
	CtColor edgeColor = _edge_color;
	
	if (_fill_color.Type == ColorNone) {
		fillColor = m_fillColor;
	}
	if (_edge_color.Type == ColorNone) {
		edgeColor = m_edgeColor;
	}
	
	if (CtDrawInfo::setColor(&m_Draw.fill, fillColor) == true)
		bRet = true;
	
	if (CtDrawInfo::setColor(&m_Draw.stroke, edgeColor) == true)
		bRet = true;

	return bRet;
}

bool CtSVG::setAlign(CtAlign _align)
{
	HALIGN	halign = m_Draw.image_style.halign;
	VALIGN	valign = m_Draw.image_style.valign;


	switch (_align & AlignHMask) {
	case AlignLeft:		halign = HALIGN_LEFT;		break;
	case AlignHCenter:	halign = HALIGN_CENTER;		break;
	case AlignRight:	halign = HALIGN_RIGHT;		break;
	default:		break;
	}

	switch (_align & AlignVMask) {
	case AlignTop:		valign = VALIGN_TOP;		break;
	case AlignVCenter:	valign = VALIGN_MIDDLE;		break;
	case AlignBottom:	valign = VALIGN_BOTTOM;		break;
	default:		break;
	}

	if ((m_Draw.image_style.halign == halign) && (m_Draw.image_style.valign == valign))
		return false;

	m_Draw.image_style.halign = halign;
	m_Draw.image_style.valign = valign;
	
	return true;
}

bool CtSVG::setAspectRatio(CtAspectRatio _ratio)
{
	ASPECT_RATIO ratio = m_Draw.image_style.aspect_ratio;
	
	switch (_ratio) {
	case AspectRatio_Default:	ratio = ASPECT_RATIO_DEFAULT;	break;
	case AspectRatio_Original:	ratio = ASPECT_RATIO_SAME;		break;
	case AspectRatio_Same:		ratio = ASPECT_RATIO_SAME;		break;
	case AspectRatio_Wide:		ratio = ASPECT_RATIO_WIDE;		break;
	case AspectRatio_Narrow:	ratio = ASPECT_RATIO_NARROW;	break;
	case AspectRatio_Special:	ratio = ASPECT_RATIO_DEFAULT;	break;
	default:		break;
	}
	
	if (m_Draw.image_style.aspect_ratio == ratio)
		return false;
	
	m_Draw.image_style.aspect_ratio = ratio;
	return true;
}

bool CtSVG::setAutoAdjust(bool _adjust)
{
	AUTO_ADJUST  adjust = m_Draw.image_style.auto_adjust;

	if (_adjust == true) {
		adjust = AUTO_ADJUST_ENABLE;
	} else {
		adjust = AUTO_ADJUST_DISABLE;
	}

	if (m_Draw.image_style.auto_adjust == adjust)
		return false;
	
	m_Draw.image_style.auto_adjust = adjust;
	return true;
}

bool CtSVG::draw()
{
	if (CtDrawInfo::drawFast() == true)
		return true;

	if (m_pCache == NULL) {
#if USE_PATH_CACHE
		m_pCache = CtDrawCache::getInstance()->referCache(*this);
#else
		m_pCache = GDI_CreateCacheSVG(m_Draw.svg);
#endif
	}
	
	return CtDraw::getInstance()->draw(*this);
}

unsigned long CtSVG::getDrawKey()
{
	unsigned long crc = 0;

	crc = CtDrawInfo::getDrawKey();
	crc = calcCRC(crc, (unsigned char*)&m_id, sizeof(m_id));
	return crc;
}

unsigned long CtSVG::getPathKey()
{
	return m_id;
}

void CtSVG::lostCache()
{
	if (m_pCache != NULL) {
		m_pCache = NULL;
	}
}

CtBitmap::CtBitmap()
{
	m_Type = DrawType_Bitmap;
	m_Draw.bitmap = NULL;
	
	m_id = IMAGE_ID_INVALID;

	m_Draw.image_style.aspect_ratio = ASPECT_RATIO_DEFAULT;
	m_Draw.image_style.auto_adjust = AUTO_ADJUST_ENABLE;
	m_Draw.image_style.halign = HALIGN_CENTER;
	m_Draw.image_style.valign = VALIGN_MIDDLE;
}

CtBitmap::CtBitmap(const GDI_IMAGE_ID _id)
{
	m_Type = DrawType_Bitmap;
	m_Draw.bitmap = NULL;
	
	setBitmap(_id);
}

CtBitmap::CtBitmap(short _width, short _height, short _buf_width, short _buf_height, const unsigned char* _data, CtImageType _type)
{
	m_Type = DrawType_Bitmap;
	m_Draw.bitmap = NULL;
	
	setBitmap(_width, _height, _buf_width, _buf_height, _data);
}

bool CtBitmap::setBitmap(const GDI_IMAGE_ID _id)
{
	if (m_id != _id) {
		if (m_id == IMAGE_ID_INVALID) {
			operator delete(m_Draw.bitmap);
		}
		m_id = _id;
		m_Draw.bitmap = GDI_GetImageBitmap(_id);
		return true;
	}
	return false;
}

bool CtBitmap::setBitmap(short _width, short _height, short _buf_width, short _buf_height, const unsigned char* _data, CtImageType _type)
{
	GDI_IMAGE_TYPE type;
	GDI_IMAGE_BITMAP* pBitmap = NULL;
	
	switch (_type) {
	case ImageType_32BPP:	type = GDI_IMAGE_TYPE_32BPP;	break;
	case ImageType_16BPP:	type = GDI_IMAGE_TYPE_16BPP;	break;
	default:				return false;
	}

	if ((pBitmap = m_Draw.bitmap) == NULL) {									/* parasoft-suppress BD-PB-NOTINIT */
		pBitmap = (GDI_IMAGE_BITMAP*)operator new(sizeof(GDI_IMAGE_BITMAP));
	} else {
		if ((pBitmap->type == type) &&
			(pBitmap->width == _width) &&
			(pBitmap->height == _height) &&
			(pBitmap->buf_width == _buf_width) &&
			(pBitmap->buf_height == _buf_height) &&
			(pBitmap->data == _data)) {
			return false;
		} else {
			if (m_id != IMAGE_ID_INVALID) {
				pBitmap = (GDI_IMAGE_BITMAP*)operator new(sizeof(GDI_IMAGE_BITMAP));
			}
		}
	}
	
	m_id = IMAGE_ID_INVALID;
	pBitmap->type = type;														/* parasoft-suppress BD-PB-NP */
	pBitmap->width = _width;													/* parasoft-suppress BD-PB-NP */
	pBitmap->height = _height;													/* parasoft-suppress BD-PB-NP */
	pBitmap->buf_width = _buf_width;											/* parasoft-suppress BD-PB-NP */
	pBitmap->buf_height = _buf_height;											/* parasoft-suppress BD-PB-NP */
	pBitmap->data = _data;														/* parasoft-suppress BD-PB-NP */
	
	m_Draw.bitmap = pBitmap;
	return true;
}

bool CtBitmap::setAlign(CtAlign _align)
{
	HALIGN	halign = m_Draw.image_style.halign;
	VALIGN	valign = m_Draw.image_style.valign;


	switch (_align & AlignHMask) {
	case AlignLeft:		halign = HALIGN_LEFT;		break;
	case AlignHCenter:	halign = HALIGN_CENTER;		break;
	case AlignRight:	halign = HALIGN_RIGHT;		break;
	default:		break;
	}

	switch (_align & AlignVMask) {
	case AlignTop:		valign = VALIGN_TOP;		break;
	case AlignVCenter:	valign = VALIGN_MIDDLE;		break;
	case AlignBottom:	valign = VALIGN_BOTTOM;		break;
	default:		break;
	}

	if ((m_Draw.image_style.halign == halign) && (m_Draw.image_style.valign == valign))
		return false;

	m_Draw.image_style.halign = halign;
	m_Draw.image_style.valign = valign;
	
	return true;
}

bool CtBitmap::setAspectRatio(CtAspectRatio _ratio)
{
	ASPECT_RATIO ratio = m_Draw.image_style.aspect_ratio;
	
	switch (_ratio) {
	case AspectRatio_Default:	ratio = ASPECT_RATIO_DEFAULT;	break;
	case AspectRatio_Original:	ratio = ASPECT_RATIO_SAME;		break;
	case AspectRatio_Same:		ratio = ASPECT_RATIO_SAME;		break;
	case AspectRatio_Wide:		ratio = ASPECT_RATIO_WIDE;		break;
	case AspectRatio_Narrow:	ratio = ASPECT_RATIO_NARROW;	break;
	case AspectRatio_Special:	ratio = ASPECT_RATIO_DEFAULT;	break;
	default:		break;
	}
	
	if (m_Draw.image_style.aspect_ratio == ratio)
		return false;
	
	m_Draw.image_style.aspect_ratio = ratio;
	return true;
}

bool CtBitmap::setAutoAdjust(bool _adjust)
{
	AUTO_ADJUST  adjust = m_Draw.image_style.auto_adjust;

	if (_adjust == true) {
		adjust = AUTO_ADJUST_ENABLE;
	} else {
		adjust = AUTO_ADJUST_DISABLE;
	}

	if (m_Draw.image_style.auto_adjust == adjust)
		return false;
	
	m_Draw.image_style.auto_adjust = adjust;
	return true;
}

bool CtBitmap::draw()
{
	if (CtDrawInfo::drawFast() == true)
		return true;
	
	return CtDraw::getInstance()->draw(*this);
}

unsigned long CtBitmap::getDrawKey()
{
	unsigned long crc = 0;

	crc = CtDrawInfo::getDrawKey();
	crc = calcCRC(crc, (unsigned char*)&m_id, sizeof(m_id));
	
	return crc;
}


CtYUV::CtYUV()
{
	m_Type = DrawType_YUV;

	m_Draw.yuv = NULL;
	m_Draw.image_style.aspect_ratio = ASPECT_RATIO_SAME;
	m_Draw.image_style.auto_adjust = AUTO_ADJUST_ENABLE;
	m_Draw.image_style.halign = HALIGN_CENTER;
	m_Draw.image_style.valign = VALIGN_MIDDLE;
}

CtYUV::CtYUV(short _width, short _height, short _y_plane_size, short _plane_stride, short _plane_height, const unsigned char* _y_plane, const unsigned char* _c_plane, CtImageType _type)
{
	m_Type = DrawType_YUV;
	m_Draw.yuv = NULL;
	
	setYUV(_width, _height, _y_plane_size, _plane_stride, _plane_height, _y_plane, _c_plane, _type);
}

bool CtYUV::setYUV(short _width, short _height, short _y_plane_size, short _plane_stride, short _plane_height, const unsigned char* _y_plane, const unsigned char* _c_plane, CtImageType _type)
{
	GDI_IMAGE_TYPE type;
	GDI_IMAGE_YUV*	pYUV = NULL;
	
	switch (_type) {
	case ImageType_YUV420:	type = GDI_IMAGE_TYPE_YUV420S;		break;
	case ImageType_YUV422:	type = GDI_IMAGE_TYPE_YCbCr;		break;
	default:				return false;
	}

	if ((pYUV = m_Draw.yuv) == NULL) {									/* parasoft-suppress BD-PB-NOTINIT */
		pYUV = (GDI_IMAGE_YUV*)operator new(sizeof(GDI_IMAGE_YUV));
	} else {
		if ((pYUV->type == type) &&
			(pYUV->width == _width) &&
			(pYUV->height == _height) &&
			(pYUV->y_plane_size == _y_plane_size) &&
			(pYUV->plane_stride == _plane_stride) &&
			(pYUV->plane_height == _plane_height) &&
			(pYUV->y_plane == _y_plane) &&
			(pYUV->c_plane == _c_plane)) {
			return false;
		}
	}

	pYUV->type = type;													/* parasoft-suppress BD-PB-NP */
	pYUV->width = _width;												/* parasoft-suppress BD-PB-NP */
	pYUV->height = _height;												/* parasoft-suppress BD-PB-NP */
	pYUV->y_plane_size = _y_plane_size;									/* parasoft-suppress BD-PB-NP */
	pYUV->plane_stride = _plane_stride;									/* parasoft-suppress BD-PB-NP */
	pYUV->plane_height = _plane_height;									/* parasoft-suppress BD-PB-NP */
	pYUV->y_plane = _y_plane;											/* parasoft-suppress BD-PB-NP */
	pYUV->c_plane = _c_plane;											/* parasoft-suppress BD-PB-NP */
	
	m_Draw.yuv = pYUV;													/* parasoft-suppress BD-PB-NP */
	return true;
}

bool CtYUV::setAlign(CtAlign _align)
{
	HALIGN	halign = m_Draw.image_style.halign;
	VALIGN	valign = m_Draw.image_style.valign;


	switch (_align & AlignHMask) {
	case AlignLeft:		halign = HALIGN_LEFT;		break;
	case AlignHCenter:	halign = HALIGN_CENTER;		break;
	case AlignRight:	halign = HALIGN_RIGHT;		break;
	default:		break;
	}

	switch (_align & AlignVMask) {
	case AlignTop:		valign = VALIGN_TOP;		break;
	case AlignVCenter:	valign = VALIGN_MIDDLE;		break;
	case AlignBottom:	valign = VALIGN_BOTTOM;		break;
	default:		break;
	}

	if ((m_Draw.image_style.halign == halign) && (m_Draw.image_style.valign == valign))
		return false;

	m_Draw.image_style.halign = halign;
	m_Draw.image_style.valign = valign;
	
	return true;
}

bool CtYUV::setAspectRatio(CtAspectRatio _ratio)
{
	ASPECT_RATIO ratio = m_Draw.image_style.aspect_ratio;
	
	switch (_ratio) {
	case AspectRatio_Default:	ratio = ASPECT_RATIO_DEFAULT;	break;
	case AspectRatio_Original:	ratio = ASPECT_RATIO_SAME;		break;
	case AspectRatio_Same:		ratio = ASPECT_RATIO_SAME;		break;
	case AspectRatio_Wide:		ratio = ASPECT_RATIO_WIDE;		break;
	case AspectRatio_Narrow:	ratio = ASPECT_RATIO_NARROW;	break;
	case AspectRatio_Special:	ratio = ASPECT_RATIO_DEFAULT;	break;
	default:		break;
	}
	
	if (m_Draw.image_style.aspect_ratio == ratio)
		return false;
	
	m_Draw.image_style.aspect_ratio = ratio;
	return true;
}

bool CtYUV::setAutoAdjust(bool _adjust)
{
	AUTO_ADJUST  adjust = m_Draw.image_style.auto_adjust;

	if (_adjust == true) {
		adjust = AUTO_ADJUST_ENABLE;
	} else {
		adjust = AUTO_ADJUST_DISABLE;
	}

	if (m_Draw.image_style.auto_adjust == adjust)
		return false;
	
	m_Draw.image_style.auto_adjust = adjust;
	return true;
}

bool CtYUV::draw()
{
	if (CtDrawInfo::drawFast() == true)
		return true;
	
	return CtDraw::getInstance()->draw(*this);
}

unsigned long CtYUV::getDrawKey()
{
	unsigned long crc = 0;

	crc = CtDrawInfo::getDrawKey();
	crc = calcCRC(crc, (unsigned char*)&m_Draw.yuv, sizeof(m_Draw.yuv));	/* pgr0834 */
	
	return crc;
}


void CtLine::ctor()
{
	m_Type = DrawType_Line;

	m_LineStyle = UnderLine;
	m_Line.x0 = 0;
	m_Line.x1 = 0;
	m_Line.y0 = 0;
	m_Line.y1 = 0;
	setStrokeWidth(0);
	setColor(CtColor::NoColor);
	m_lineColor = CtColor::NoColor;
}

CtLine::CtLine()
{
	ctor();
}

CtLine::CtLine(CtLineStyle _style)
{
	ctor();
	setLineStyle(_style);
}

CtLine::CtLine(short _stroke_width)
{
	ctor();
	setStrokeWidth(_stroke_width);
}

CtLine::CtLine(CtLineStyle _style, short _stroke_width)
{
	ctor();
	setLineStyle(_style);
	setStrokeWidth(_stroke_width);
}

CtLine::CtLine(CtLineStyle _style, short _stroke_width, const CtColor& _color)
{
	ctor();
	setLineStyle(_style);
	setStrokeWidth(_stroke_width);
	setColor(_color);
	m_lineColor = _color;
}

bool CtLine::setRegion(short _x, short _y, short _width, short _height)
{
	bool bRet = false;
	
	if ((bRet = CtDrawInfo::setRegion(_x, _y, _width, _height)) != true) {
		return bRet;
	}

	switch (m_LineStyle) {
	case UnderLine:
		if ((m_Line.x0 == 0) &&
			(m_Line.y0 == _height) &&
			(m_Line.x1 == _width) &&
			(m_Line.y1 == _height)) {
			break;
		}
		m_Line.x0 = 0;
		m_Line.y0 = _height;
		m_Line.x1 = _width;
		m_Line.y1 = _height;
		bRet = true;
		break;
	case UpperLine:
		if ((m_Line.x0 == 0) &&
			(m_Line.y0 == 0) &&
			(m_Line.x1 == _width) &&
			(m_Line.y1 == 0)) {
			break;
		}
		m_Line.x0 = 0;
		m_Line.y0 = 0;
		m_Line.x1 = _width;
		m_Line.y1 = 0;
		bRet = true;
		break;
	case LeftLine:
		if ((m_Line.x0 == 0) &&
			(m_Line.y0 == 0) &&
			(m_Line.x1 == 0) &&
			(m_Line.y1 == _height)) {
			break;
		}
		m_Line.x0 = 0;
		m_Line.y0 = 0;
		m_Line.x1 = 0;
		m_Line.y1 = _height;
		bRet = true;
		break;
	case RightLine:
		if ((m_Line.x0 == _width) &&
			(m_Line.y0 == 0) &&
			(m_Line.x1 == _width) &&
			(m_Line.y1 == _height)) {
			break;
		}
		m_Line.x0 = _width;
		m_Line.y0 = 0;
		m_Line.x1 = _width;
		m_Line.y1 = _height;
		bRet = true;
		break;
	case TopLeftSlashLine:
		if ((m_Line.x0 == 0) &&
			(m_Line.y0 == 0) &&
			(m_Line.x1 == _width) &&
			(m_Line.y1 == _height)) {
			break;
		}
		m_Line.x0 = 0;
		m_Line.y0 = 0;
		m_Line.x1 = _width;
		m_Line.y1 = _height;
		bRet = true;
		break;
	case TopRightSlashLine:
		if ((m_Line.x0 == 0) &&
			(m_Line.y0 == _height) &&
			(m_Line.x1 == _width) &&
			(m_Line.y1 == 0)) {
			break;
		}
		m_Line.x0 = 0;
		m_Line.y0 = _height;
		m_Line.x1 = _width;
		m_Line.y1 = 0;
		bRet = true;
		break;
	default:
		break;
	}
	return bRet;
}

bool CtLine::setLine(CtLineStyle _style, short _stroke_width, const CtColor& _color)
{
	bool bRet = false;

	if (setLineStyle(_style) == true)
		bRet = true;

	if (setStrokeWidth(_stroke_width) == true)
		bRet = true;

	if (setColor(_color) == true)
		bRet = true;

	if (bRet == true) {
		m_lineColor = _color;
	}
	
	return bRet;
}

bool CtLine::setLine(const CtLine& Line)
{
	if (m_LineStyle != Line.m_LineStyle) {
		m_LineStyle = Line.m_LineStyle;
	}
	m_Line = Line.m_Line;

	m_lineColor = Line.getFillColor();
	
	return true;
}

bool CtLine::setStrokeWidth(short _stroke_width)
{
	if (m_Line.line_width != _stroke_width) {				/* parasoft-suppress BD-PB-NOTINIT */
		m_Line.line_width = _stroke_width;
		return true;
	}
	return false;
}

bool CtLine::setLineStyle(CtLineStyle _style)
{
	if (m_LineStyle != _style) {
		m_LineStyle = _style;
		return true;
	}
	return false;
}

bool CtLine::setColor(const CtColor& _color, const CtColor& _stroke_color)
{
	CtColor lineColor = _stroke_color;

	if (_stroke_color.Type == ColorNone) {
		lineColor = m_lineColor;
	}
	
	return CtDrawInfo::setColor(&m_Line.line_color, lineColor);
}

bool CtLine::setColor(const CtColor& _color)
{
	CtColor lineColor = _color;

	if (_color.Type == ColorNone) {
		lineColor = m_lineColor;
	}
	
	return CtDrawInfo::setColor(&m_Line.line_color, lineColor);
}

CtColor CtLine::getFillColor() const
{
	return CtDrawInfo::getColor(&m_Line.line_color);
}

bool CtLine::draw()
{
	if (CtDrawInfo::drawFast() == true)
		return true;
	
	return CtDraw::getInstance()->draw(*this);
}

unsigned long CtLine::getDrawKey()
{
	unsigned long crc = 0;

	crc = CtDrawInfo::getDrawKey();
	crc = calcCRC(crc, (unsigned char*)&m_LineStyle, sizeof(m_LineStyle));
	crc = calcCRC(crc, (unsigned char*)&m_lineColor, sizeof(m_lineColor));
	
	return crc;
}

void CtRect::ctor()
{
	m_Type = DrawType_Rect;
	m_Rect.stroke_width = 0;
	setColor(CtColor::NoColor, CtColor::NoColor);
	m_fillColor = CtColor::NoColor;
	m_edgeColor = CtColor::NoColor;
}

CtRect::CtRect()
{
	ctor();
}

CtRect::CtRect(const CtColor& _fill_color)
{
	ctor();
	setColor(_fill_color);
	m_fillColor = _fill_color;
}

CtRect::CtRect(short _stroke_width, const CtColor& _stroke_color)
{
	ctor();
	setStrokeWidth(_stroke_width);
	setColor(CtColor::NoColor, _stroke_color);
	m_edgeColor = _stroke_color;
}

CtRect::CtRect(const CtColor& _fill_color, short _stroke_width, const CtColor& _stroke_color)
{
	ctor();
	setStrokeWidth(_stroke_width);
	setColor(_fill_color, _stroke_color);
	m_fillColor = _fill_color;
	m_edgeColor = _stroke_color;
}

bool CtRect::setRect(const CtColor& _fill_color, short _stroke_width, const CtColor& _stroke_color)
{
	bool bRet = false;
	
	if (setStrokeWidth(_stroke_width) == true)
		bRet = true;

	if (setColor(_fill_color, _stroke_color) == true)
		bRet = true;

	if (bRet == true) {
		m_fillColor = _fill_color;
		m_edgeColor = _stroke_color;
	}
	
	return bRet;
}

bool CtRect::setRect(const CtRect& Rect)
{
	m_Rect = Rect.m_Rect;
	m_fillColor = Rect.getFillColor();
	m_edgeColor = Rect.getEdgeColor();
	return true;
}

bool CtRect::setStrokeWidth(short _stroke_width)
{
	if (m_Rect.stroke_width != (unsigned short)_stroke_width) {
		m_Rect.stroke_width = _stroke_width;
		return true;
	}
	return false;
}

bool CtRect::setColor(const CtColor& _fill_color,  const CtColor& _stroke_color)
{
	bool bRet = false;
	CtColor fillColor = _fill_color;
	CtColor edgeColor = _stroke_color;

	if (_fill_color.Type == ColorNone) {
		fillColor = m_fillColor;
	}
	if (_stroke_color.Type == ColorNone) {
		edgeColor = m_edgeColor;
	}
	
	if (CtDrawInfo::setColor(&m_Rect.fill_color, fillColor) == true)
		bRet = true;
	if (CtDrawInfo::setColor(&m_Rect.stroke_color, edgeColor) == true)
		bRet = true;
	
	return bRet;
}
bool CtRect::setColor(const CtColor& _fill_color)
{
	bool bRet = false;
	CtColor fillColor = _fill_color;

	if (_fill_color.Type == ColorNone) {
		fillColor = m_fillColor;
	}
	
	if (CtDrawInfo::setColor(&m_Rect.fill_color, fillColor) == true)
		bRet = true;
	
	return bRet;
}

CtColor CtRect::getFillColor() const
{
	return CtDrawInfo::getColor(&m_Rect.fill_color);
}

CtColor CtRect::getEdgeColor() const
{
	return CtDrawInfo::getColor(&m_Rect.stroke_color);
}


bool CtRect::draw()
{
	if (CtDrawInfo::drawFast() == true)
		return true;
	
	return CtDraw::getInstance()->draw(*this);
}

unsigned long CtRect::getDrawKey()
{
	unsigned long crc = 0;

	crc = CtDrawInfo::getDrawKey();
	crc = calcCRC(crc, (unsigned char*)&m_Rect, sizeof(m_Rect));
	//CtDebugPrint(CtDbg, "Rect Key : %08X\n", crc);
	return crc;
}

void CtRoundRect::ctor()
{
	m_Type = DrawType_RoundRect;

	setStrokeWidth(0);
	setArc(10, 10);
	setColor(CtColor::NoColor, CtColor::NoColor);
	m_fillColor = CtColor::NoColor;
	m_edgeColor = CtColor::NoColor;
}

CtRoundRect::CtRoundRect()
{
	ctor();
}

CtRoundRect::CtRoundRect(const CtColor& _fill_color)
{
	ctor();
	setColor(_fill_color);
	m_fillColor = _fill_color;
}

CtRoundRect::CtRoundRect(short _stroke_width, const CtColor& _stroke_color)
{
	ctor();
	setStrokeWidth(_stroke_width);
	setColor(CtColor::NoColor, _stroke_color);
	m_edgeColor = _stroke_color;
}

CtRoundRect::CtRoundRect(const CtColor& _fill_color, short _stroke_width, const CtColor& _stroke_color)
{
	ctor();
	setStrokeWidth(_stroke_width);
	setColor(_fill_color, _stroke_color);
	m_fillColor = _fill_color;
	m_edgeColor = _stroke_color;
}

CtRoundRect::CtRoundRect(short _arc_width, short _arc_height, const CtColor& _fill_color, short _stroke_width, const CtColor& _stroke_color)
{
	ctor();
	setStrokeWidth(_stroke_width);
	setArc(_arc_width, _arc_height);
	setColor(_fill_color, _stroke_color);
	m_fillColor = _fill_color;
	m_edgeColor = _stroke_color;
}

bool CtRoundRect::setRoundRect(short _arc_width, short _arc_height, const CtColor& _fill_color, short _stroke_width, const CtColor& _stroke_color)
{
	bool bRet = false;
	
	if (setStrokeWidth(_stroke_width) == true)
		bRet = true;
	
	if (setArc(_arc_width, _arc_height) == true)
		bRet = true;
	
	if (setColor(_fill_color, _stroke_color) == true)
		bRet = true;
	
	if (bRet == true) {
		m_fillColor = _fill_color;
		m_edgeColor = _stroke_color;
	}
	return bRet;
	
}

bool CtRoundRect::setRoundRect(const CtRoundRect& RoundRect)
{
	m_RRect = RoundRect.m_RRect;
	m_fillColor = RoundRect.getFillColor();
	m_edgeColor = RoundRect.getEdgeColor();
	return true;
}

bool CtRoundRect::setStrokeWidth(short _stroke_width)
{
	if (m_RRect.stroke_width != (unsigned short)_stroke_width) {/* parasoft-suppress BD-PB-NOTINIT */
		m_RRect.stroke_width = _stroke_width;
		return true;
	}
	return false;
}

bool CtRoundRect::setArc(short _arc_width, short _arc_height)
{
	if (m_RRect.arc_width != _arc_width || m_RRect.arc_height != _arc_height) {
		m_RRect.arc_width = _arc_width;
		m_RRect.arc_height = _arc_height;
		return true;
	}
	return false;
}


bool CtRoundRect::setColor(const CtColor& _fill_color, const CtColor& _stroke_color)
{
	bool bRet = false;
	CtColor fillColor = _fill_color;
	CtColor edgeColor = _stroke_color;

	if (_fill_color.Type == ColorNone) {
		fillColor = m_fillColor;
	}
	if (_stroke_color.Type == ColorNone) {
		edgeColor = m_edgeColor;
	}
	
	if (CtDrawInfo::setColor(&m_RRect.fill_color, fillColor) == true)
		bRet = true;
	if (CtDrawInfo::setColor(&m_RRect.stroke_color, edgeColor) == true)
		bRet = true;
	
	return bRet;
}

bool CtRoundRect::setColor(const CtColor& _fill_color)
{
	bool bRet = false;
	CtColor fillColor = _fill_color;

	if (_fill_color.Type == ColorNone) {
		fillColor = m_fillColor;
	}
	
	if (CtDrawInfo::setColor(&m_RRect.fill_color, fillColor) == true)
		bRet = true;
	
	return bRet;
}

CtColor CtRoundRect::getFillColor() const
{
	return CtDrawInfo::getColor(&m_RRect.fill_color);
}

CtColor CtRoundRect::getEdgeColor() const
{
	return CtDrawInfo::getColor(&m_RRect.stroke_color);
}

bool CtRoundRect::draw()
{
	if (CtDrawInfo::drawFast() == true)
		return true;
	
	return CtDraw::getInstance()->draw(*this);
}

unsigned long CtRoundRect::getDrawKey()
{
	unsigned long crc = 0;

	crc = CtDrawInfo::getDrawKey();
	crc = calcCRC(crc, (unsigned char*)&m_RRect, sizeof(m_RRect));
	
	return crc;
}

void CtEllipse::ctor()
{
	m_Type = DrawType_Ellipse;
	setStrokeWidth(0);
	setColor(CtColor::NoColor, CtColor::NoColor);
	m_fillColor = CtColor::NoColor;
	m_edgeColor = CtColor::NoColor;
}

CtEllipse::CtEllipse() : m_Ellipse(GDI_DRAW_ELLIPSE())
{
	ctor();
}

CtEllipse::CtEllipse(const CtColor& _fill_color)
{
	ctor();
	setColor(_fill_color);
	m_fillColor = _fill_color;
}

CtEllipse::CtEllipse(short _stroke_width, const CtColor& _stroke_color)
{
	ctor();
	setStrokeWidth(_stroke_width);
	setColor(CtColor::NoColor, _stroke_color);
	m_edgeColor = _stroke_color;
}

CtEllipse::CtEllipse(const CtColor& _fill_color, short _stroke_width, const CtColor& _stroke_color)
{
	ctor();
	setStrokeWidth(_stroke_width);
	setColor(_fill_color, _stroke_color);
	m_fillColor = _fill_color;
	m_edgeColor = _stroke_color;
}

bool CtEllipse::setEllipse(const CtColor& _fill_color, short _stroke_width, const CtColor& _stroke_color)
{
	bool bRet = false;
	
	if (setStrokeWidth(_stroke_width) == true)
		bRet = true;

	if (setColor(_fill_color, _stroke_color) == true)
		bRet = true;

	if (bRet == true) {
		m_fillColor = _fill_color;
		m_edgeColor = _stroke_color;
	}
	
	return bRet;
}

bool CtEllipse::setEllipse(const CtEllipse& Ellipse)
{
	m_Ellipse = Ellipse.m_Ellipse;
	m_fillColor = Ellipse.getFillColor();
	m_edgeColor = Ellipse.getEdgeColor();
	return true;
}

bool CtEllipse::setStrokeWidth(short _stroke_width)
{
	if (m_Ellipse.stroke_width != (unsigned short)_stroke_width) {	/* parasoft-suppress BD-PB-NOTINIT */
		m_Ellipse.stroke_width = _stroke_width;
		return true;
	}
	return false;
}

bool CtEllipse::setColor(const CtColor& _fill_color, const CtColor& _stroke_color)
{
	bool bRet = false;
	CtColor fillColor = _fill_color;
	CtColor edgeColor = _stroke_color;

	if (_fill_color.Type == ColorNone) {
		fillColor = m_fillColor;
	}
	if (_stroke_color.Type == ColorNone) {
		edgeColor = m_edgeColor;
	}
	
	if (CtDrawInfo::setColor(&m_Ellipse.fill_color, fillColor) == true)
		bRet = true;
	
	if (CtDrawInfo::setColor(&m_Ellipse.stroke_color, edgeColor) == true)
		bRet = true;
	
	return bRet;
}

bool CtEllipse::setColor(const CtColor& _fill_color)
{
	bool bRet = false;
	CtColor fillColor = _fill_color;

	if (_fill_color.Type == ColorNone) {
		fillColor = m_fillColor;
	}
	
	if (CtDrawInfo::setColor(&m_Ellipse.fill_color, fillColor) == true)
		bRet = true;
	
	return bRet;
}

CtColor CtEllipse::getFillColor() const
{
	return CtDrawInfo::getColor(&m_Ellipse.fill_color);
}

CtColor CtEllipse::getEdgeColor() const
{
	return CtDrawInfo::getColor(&m_Ellipse.stroke_color);
}

bool CtEllipse::draw()
{
	if (CtDrawInfo::drawFast() == true)
		return true;
	
	return CtDraw::getInstance()->draw(*this);
}

unsigned long CtEllipse::getDrawKey()
{
	unsigned long crc = 0;

	crc = CtDrawInfo::getDrawKey();
	crc = calcCRC(crc, (unsigned char*)&m_Ellipse, sizeof(m_Ellipse));
	
	return crc;
}

CtRecViewFontSet::CtRecViewFontSet()
{
	ctor();
}

CtRecViewFontSet::CtRecViewFontSet(FontSetType _type)
{
	FONT_ATTRIBUTE type = (FONT_ATTRIBUTE)(_type & CT_FONT_TYPE_MASK);
	ctor();
	setFontAttribute(_type);
	edgeColor = (FONT_ATTRIBUTE_OUTLINE == type) ? CtColor::White : CtColor::NoColor;
}

CtRecViewFontSet::CtRecViewFontSet(FontSetType _type, const CtColor& _fontColor)
{
	ctor();
	setFontAttribute(_type);
	setColor(_fontColor);
}

CtRecViewFontSet::CtRecViewFontSet(FontSetType _type, const CtColor& _fontColor, const CtColor& _edgeColor)
{
	ctor();
	setFontAttribute(_type);
	setColor(_fontColor, _edgeColor);
}

void CtRecViewFontSet::ctor() {
	fontStyle.font_size = 0;
	fontStyle.locale = LOCALE_FX;
	fontStyle.aspect_ratio = ASPECT_RATIO_DEFAULT;
	fontStyle.auto_adjust = AUTO_ADJUST_ENABLE;
	fontStyle.attr = FONT_ATTRIBUTE_OUTLINE;
	fontStyle.halign = HALIGN_LEFT;
	fontStyle.valign = VALIGN_DEFAULT;
	fontStyle.isWriteOneChar = true;
	fontColor = CtColor::White;
	edgeColor = CtColor::Black;
}

void CtRecViewFontSet::setFontAttribute(FontSetType _type) {
	fontStyle.halign = ((0 != (_type & CT_FONT_ALIGN_CENTER) ? HALIGN_CENTER
		: (0 != (_type & CT_FONT_ALIGN_RIGHT) ? HALIGN_RIGHT
			: HALIGN_LEFT)));

	fontStyle.valign = ((0 != (_type & CT_FONT_VALIGN_TOP) ? VALIGN_TOP
		: (0 != (_type & CT_FONT_VALIGN_MIDDLE) ? VALIGN_MIDDLE
			: (0 != (_type & CT_FONT_VALIGN_BOTTOM) ? VALIGN_BOTTOM
				: VALIGN_DEFAULT))));
}
