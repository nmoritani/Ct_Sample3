#include "stdafx.h"
#include "SvgLine.h"

//デストラクタ
SvgLine::~SvgLine()
{
}

//属性解析
PARSE_RESULT SvgLine::parse_attribute(const char *att[])
{
	if (!strcmp(att[0], "x1")) {
		//x
		m_x1 = (float)atof(att[1]);
		return PARSED;
	} else
	if (!strcmp(att[0], "y1")) {
		//y
		m_y1 = (float)atof(att[1]);
		return PARSED;
	} else
	if (!strcmp(att[0], "x2")) {
		//rx
		m_x2 = (float)atof(att[1]);
		return PARSED;
	} else
	if (!strcmp(att[0], "y2")) {
		//ry
		m_y2 = (float)atof(att[1]);
		return PARSED;
	} else
	{
		//スーパークラスのメソッド呼び出し
		return super::parse_attribute(att);
	}
}

//パスに変換
SvgPath *SvgLine::cnv_to_path()
{
	SvgPath		*path = NEW SvgPath(this);

	//Move
	path->add_command(SVG_CMD_M);
	path->add_coord(m_x1);
	path->add_coord(m_y1);
	//Line
	path->add_command(SVG_CMD_L);
	path->add_coord(m_x2);
	path->add_coord(m_y2);

	return path;
}

