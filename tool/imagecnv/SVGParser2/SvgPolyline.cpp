#include "stdafx.h"
#include "SvgPolyline.h"

//デストラクタ
SvgPolyline::~SvgPolyline()
{
}

//属性解析
PARSE_RESULT SvgPolyline::parse_attribute(const char *att[])
{
	if (!strcmp(att[0], "points")) {
		return parse_points(att[1]);
	} else
	{
		//スーパークラスのメソッド呼び出し
		return super::parse_attribute(att);
	}
}

//座標データ解析
PARSE_RESULT SvgPolyline::parse_points(const char *data)
{
	int				i;
	float			coord;


	//座標解析
	//空白を飛ばす
	data = svgutil_skip_space(data);
	while (*data) {
		//座標はX,Yの２個セット
		for (i = 0; i < 2; i++) {
			//数値以外はエラー
			if (!svgutil_is_num_start(*data)) {
				fprintf(stderr, "Invalid Data '%c'\n", *data);
				goto error;
			}
			coord = (float)strtod(data, (char**)&data);
			//座標追加
			SVG_DPRINTF("%f,", coord);
			m_coords.push_back(coord);
			//空白を飛ばす
			data = svgutil_skip_space(data);
			//','なら飛ばす
			if (*data == ',') {
				data++;
				//,の後の空白を飛ばす
				data = svgutil_skip_space(data);
			}
		}
		SVG_DPRINTF("\n");
	}

	return PARSED;
error:
	//データクリアする
	m_coords.clear();

	return PARSE_ERROR;
}

//パスに変換
SvgPath *SvgPolyline::cnv_to_path()
{
	SVG_CMD					cmd;
	SVGCOORDS::iterator		i;

	if (m_coords.size() == 0) {
		return NULL;
	}

	SvgPath		*path = NEW SvgPath(this);

	i = m_coords.begin();
	cmd = SVG_CMD_M;
	while (i != m_coords.end()) {
		path->add_command(cmd);
		path->add_coord(*i);		//X
		++i;
		path->add_coord(*i);		//Y
		++i;
		//
		cmd = SVG_CMD_L;	//２つめ以降はLineTo
	}

	//Polylineは閉じない

	return path;
}

