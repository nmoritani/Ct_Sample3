#include "stdafx.h"
#include "string.h"
#include "SvgStop.h"
#include "SvgUtil.h"

SvgStop::SvgStop(SvgParser *parser, SvgObject *parent)
	: SvgObject(parser, parent)
{
	m_type = SVG_TYPE_STOP;
	m_offset = 0;
}

SvgStop::~SvgStop()
{
}

//属性解析
PARSE_RESULT SvgStop::parse_attribute(const char *att[])
{
	if (!strcmp(att[0], "offset")) {
		//offset
		m_offset = (float)atof(att[1]);
		SVG_DPRINTF("offset=%f\n", m_offset);
		return PARSED;
	} else
	{
		//スーパークラスのメソッド呼び出し
		return super::parse_attribute(att);
	}
}


