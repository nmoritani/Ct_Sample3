#include "stdafx.h"
#include "SvgParser.h"
#include "SvgGradient.h"
#include "SvgUtil.h"

SvgGradient::SvgGradient(SvgParser *parser, SvgObject *parent)
	: super(parser, parent)
{
	m_type = SVG_TYPE_GRADIENT;
	m_ref_obj = NULL;
}

SvgGradient::~SvgGradient()
{
	vector<SvgStop*>::iterator i;

	for (i = m_stops.begin(); i != m_stops.end(); ++i) {
		delete *i;
	}
}

//属性解析
PARSE_RESULT SvgGradient::parse_attribute(const char *att[])
{
	if (!strcmp(att[0], "id")) {
		//id
		m_id = att[1];
		return PARSED;
	} else
	if (!strcmp(att[0], "xlink:href")) {
		//href
		//制限：すでに定義されているものだけ検索する
		const char *p = att[1];
		p++;	//#を飛ばす
		m_ref_obj = dynamic_cast<SvgGradient*>(parser()->find_defs(p));
		if (m_ref_obj == NULL) {
			fprintf(stderr, "ERROR: Not Found Object %s\n", att[1]);
			return PARSE_ERROR;
		}
		return PARSED;
	} else
	{
		//スーパークラスのメソッド呼び出し
		return super::parse_attribute(att);
	}
}

