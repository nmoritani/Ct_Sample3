#include "stdafx.h"
#include "SvgSvg.h"
#include "SvgUtil.h"

SvgSvg::SvgSvg(SvgParser *parser, SvgObject *parent)
	: super(parser, parent)
{
	m_type = SVG_TYPE_SVG;
	m_width = 0;
	m_height = 0;
}

SvgSvg::~SvgSvg()
{
}

//属性解析
PARSE_RESULT SvgSvg::parse_attribute(const char *att[])
{
	if (!strcmp(att[0], "width")) {
		//width
		m_width = (float)atof(att[1]);
		return PARSED;
	} else
	if (!strcmp(att[0], "height")) {
		//height
		m_height = (float)atof(att[1]);
		return PARSED;
	} else
	{
		//スーパークラスのメソッド呼び出し
		return super::parse_attribute(att);
	}
}

