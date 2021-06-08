#include "stdafx.h"
#include "SvgParser.h"
#include "SvgRadialGradient.h"
#include "SvgUtil.h"

SvgRadialGradient::SvgRadialGradient(SvgParser *parser, SvgObject *parent)
	: super(parser, parent)
{
	m_type = SVG_TYPE_RADIALGRADIENT;
	m_cx = 0;
	m_cy = 0;
	m_fx = -999999;
	m_fy = -999999;
	m_r  = 0;
}

SvgRadialGradient::~SvgRadialGradient()
{
}

//属性解析
PARSE_RESULT SvgRadialGradient::parse_attribute(const char *att[])
{
	if (!strcmp(att[0], "cx")) {
		//cx
		m_cx = (float)atof(att[1]);
		return PARSED;
	} else
	if (!strcmp(att[0], "cy")) {
		//cy
		m_cy = (float)atof(att[1]);
		return PARSED;
	} else
	if (!strcmp(att[0], "fx")) {
		//fx
		m_fx = (float)atof(att[1]);
		return PARSED;
	} else
	if (!strcmp(att[0], "fy")) {
		//fy
		m_fy = (float)atof(att[1]);
		return PARSED;
	} else
	if (!strcmp(att[0], "r")) {
		//r
		m_r = (float)atof(att[1]);
		return PARSED;
	} else
	{
		//スーパークラスのメソッド呼び出し
		return super::parse_attribute(att);
	}
}

PARSE_RESULT SvgRadialGradient::parse_attribute_end()
{
	//m_fx,m_fyが未定義だった場合、補正する。
	if(m_fx == -999999) {
		m_fx = m_cx;
	}
	if(m_fy == -999999) {
		m_fy = m_cy;
	}
	
	return PARSED;
}
