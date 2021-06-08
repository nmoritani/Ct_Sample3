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
		//�X�[�p�[�N���X�̃��\�b�h�Ăяo��
		return super::parse_attribute(att);
	}
}

//�p�X�f�[�^���
PARSE_RESULT SvgPath::parse_d(const char *data)
{
	char			cmd;
	SVG_CMD			cmd_id;
	SVG_CMD			last_cmd_id = SVG_CMD_MAX;
	int				data_num;
	int				i;
	float			coord;

	//�󔒂��΂�
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
			//���l�ȊO�̏ꍇ�̓G���[
			if (!svgutil_is_num_start(*data)) {
				fprintf(stderr, "Unknown Command '%c'\n", cmd);
				goto error;
			}
			//�����R�}���h�̌J��Ԃ� M,m��L,l�ɒu������
			if (last_cmd_id == SVG_CMD_M) {
				cmd_id = SVG_CMD_L;
			} else 
			if (last_cmd_id == SVG_CMD_m) {
				cmd_id = SVG_CMD_l;
			} else
			{
				cmd_id = last_cmd_id;
			}
			data--;		//switch�̌��data++�����̂�-1���Ă���
			break;
		}
		//�R�}���h���΂�
		data++;

		//���W��
		data_num = svgutil_cmd_coords_num(cmd_id);

		//�R�}���h�ǉ�
		SVG_DPRINTF("%c ", svgutil_cmd_str(cmd_id));
#if 1
		m_commands.push_back(cmd_id);
#else
		//�ŏ���m��M�Ƃ��Ĉ����K�v������H
		if (last_cmd_id == SVG_CMD_MAX && cmd_id == SVG_CMD_m) {
			m_commands.push_back(SVG_CMD_M);
		} else {
			m_commands.push_back(cmd_id);
		}
#endif

		//���W���
		//�󔒂��΂�
		data = svgutil_skip_space(data);
		for (i = 0; i < data_num; i++) {
			//���l�ȊO�̓G���[
			if (!svgutil_is_num_start(*data)) {
				fprintf(stderr, "Invalid Data '%c'\n", *data);
				goto error;
			}
			coord = (float)strtod(data, (char**)&data);
			//���W�ǉ�
			SVG_DPRINTF("%f,", coord);
			m_coords.push_back(coord);
			//���̐��l�܂Ŕ�΂�
			data = svgutil_skip_to_next_token(data);
		}
		SVG_DPRINTF("\n");

		last_cmd_id = cmd_id;
	}

	return PARSED;
error:
	//�f�[�^�N���A����
	m_commands.clear();
	m_coords.clear();

	return PARSE_ERROR;
}
