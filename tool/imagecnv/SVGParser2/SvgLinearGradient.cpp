#include "stdafx.h"
#include "SvgParser.h"
#include "SvgLinearGradient.h"
#include "SvgUtil.h"

SvgLinearGradient::SvgLinearGradient(SvgParser *parser, SvgObject *parent)
	: super(parser, parent)
{
	m_type = SVG_TYPE_LINEARGRADIENT;
	m_x1 = -1;
	m_y1 = -1;
	m_x2 = -1;
	m_y2 = -1;
}

SvgLinearGradient::~SvgLinearGradient()
{
}

//属性解析
PARSE_RESULT SvgLinearGradient::parse_attribute(const char *att[])
{
	if (!strcmp(att[0], "x1")) {
		//x1
		m_x1 = (float)atof(att[1]);
		return PARSED;
	} else
	if (!strcmp(att[0], "y1")) {
		//y1
		m_y1 = (float)atof(att[1]);
		return PARSED;
	} else
	if (!strcmp(att[0], "x2")) {
		//x2
		m_x2 = (float)atof(att[1]);
		return PARSED;
	} else
	if (!strcmp(att[0], "y2")) {
		//y2
		m_y2 = (float)atof(att[1]);
		return PARSED;
	} else
	{
		//スーパークラスのメソッド呼び出し
		return super::parse_attribute(att);
	}
}

