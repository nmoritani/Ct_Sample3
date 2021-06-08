#include "stdafx.h"
#include "SvgPath.h"
#include "SvgUtil.h"

SvgPath::~SvgPath()
{
}

PARSE_RESULT SvgPath::parse_attribute(const char *att[])
{
	if (!strcmp(att[0], "d")) {
		return parse_d(att[1]);
	} else
	{
		//スーパークラスのメソッド呼び出し
		return super::parse_attribute(att);
	}
}

//パスデータ解析
PARSE_RESULT SvgPath::parse_d(const char *data)
{
	char			cmd;
	SVG_CMD			cmd_id;
	SVG_CMD			last_cmd_id = SVG_CMD_MAX;
	int				data_num;
	int				i;
	float			coord;

	//空白を飛ばす
	data = svgutil_skip_space(data);

	while (*data) {
		cmd = *data;
		switch (cmd) {
		case 'M':
			cmd_id = SVG_CMD_M;
			break;
		case 'm':
			cmd_id = SVG_CMD_m;
			break;
		case 'Z':
		case 'z':
			cmd_id = SVG_CMD_z;
			break;
		case 'L':
			cmd_id = SVG_CMD_L;
			break;
		case 'l':
			cmd_id = SVG_CMD_l;
			break;
		case 'H':
			cmd_id = SVG_CMD_H;
			break;
		case 'h':
			cmd_id = SVG_CMD_h;
			break;
		case 'V':
			cmd_id = SVG_CMD_V;
			break;
		case 'v':
			cmd_id = SVG_CMD_v;
			break;
		case 'C':
			cmd_id = SVG_CMD_C;
			break;
		case 'c':
			cmd_id = SVG_CMD_c;
			break;
		case 'S':
			cmd_id = SVG_CMD_S;
			break;
		case 's':
			cmd_id = SVG_CMD_s;
			break;
		case 'Q':
			cmd_id = SVG_CMD_Q;
			break;
		case 'q':
			cmd_id = SVG_CMD_q;
			break;
		case 'T':
			cmd_id = SVG_CMD_T;
			break;
		case 't':
			cmd_id = SVG_CMD_t;
			break;
		case 'A':
			cmd_id = SVG_CMD_A;
			break;
		case 'a':
			cmd_id = SVG_CMD_a;
			break;
		default:
			//数値以外の場合はエラー
			if (!svgutil_is_num_start(*data)) {
				fprintf(stderr, "Unknown Command '%c'\n", cmd);
				goto error;
			}
			//同じコマンドの繰り返し M,mはL,lに置き換え
			if (last_cmd_id == SVG_CMD_M) {
				cmd_id = SVG_CMD_L;
			} else 
			if (last_cmd_id == SVG_CMD_m) {
				cmd_id = SVG_CMD_l;
			} else
			{
				cmd_id = last_cmd_id;
			}
			data--;		//switchの後でdata++されるので-1しておく
			break;
		}
		//コマンドを飛ばす
		data++;

		//座標数
		data_num = svgutil_cmd_coords_num(cmd_id);

		//コマンド追加
		SVG_DPRINTF("%c ", svgutil_cmd_str(cmd_id));
#if 1
		m_commands.push_back(cmd_id);
#else
		//最初のmはMとして扱う必要がある？
		if (last_cmd_id == SVG_CMD_MAX && cmd_id == SVG_CMD_m) {
			m_commands.push_back(SVG_CMD_M);
		} else {
			m_commands.push_back(cmd_id);
		}
#endif

		//座標解析
		//空白を飛ばす
		data = svgutil_skip_space(data);
		for (i = 0; i < data_num; i++) {
			//数値以外はエラー
			if (!svgutil_is_num_start(*data)) {
				fprintf(stderr, "Invalid Data '%c'\n", *data);
				goto error;
			}
			coord = (float)strtod(data, (char**)&data);
			//座標追加
			SVG_DPRINTF("%f,", coord);
			m_coords.push_back(coord);
			//次の数値まで飛ばす
			data = svgutil_skip_to_next_token(data);
		}
		SVG_DPRINTF("\n");

		last_cmd_id = cmd_id;
	}

	return PARSED;
error:
	//データクリアする
	m_commands.clear();
	m_coords.clear();

	return PARSE_ERROR;
}
