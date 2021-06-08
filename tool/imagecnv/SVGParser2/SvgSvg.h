#ifndef _SVGSVG_H_
#define _SVGSVG_H_

#include "SvgObject.h"
#include "SvgGroup.h"

class SvgSvg : public SvgGroup {
	typedef SvgGroup	super;
public:

protected:
	float				m_width;
	float				m_height;
public:
	//コンストラクタ
	SvgSvg(SvgParser *parser, SvgObject *parent);
	//デストラクタ
	virtual ~SvgSvg();
	//属性解析
	virtual PARSE_RESULT parse_attribute(const char *att[]);
	//
	float width() const { return m_width; }
	float height() const { return m_height; }
};

#endif
