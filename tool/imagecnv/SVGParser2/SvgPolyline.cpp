#include "stdafx.h"
#include "SvgPolyline.h"

//�f�X�g���N�^
SvgPolyline::~SvgPolyline()
{
}

//�������
PARSE_RESULT SvgPolyline::parse_attribute(const char *att[])
{
	if (!strcmp(att[0], "points")) {
		return parse_points(att[1]);
	} else
	{
		//�X�[�p�[�N���X�̃��\�b�h�Ăяo��
		return super::parse_attribute(att);
	}
}

//���W�f�[�^���
PARSE_RESULT SvgPolyline::parse_points(const char *data)
{
	int				i;
	float			coord;


	//���W���
	//�󔒂��΂�
	data = svgutil_skip_space(data);
	while (*data) {
		//���W��X,Y�̂Q�Z�b�g
		for (i = 0; i < 2; i++) {
			//���l�ȊO�̓G���[
			if (!svgutil_is_num_start(*data)) {
				fprintf(stderr, "Invalid Data '%c'\n", *data);
				goto error;
			}
			coord = (float)strtod(data, (char**)&data);
			//���W�ǉ�
			SVG_DPRINTF("%f,", coord);
			m_coords.push_back(coord);
			//�󔒂��΂�
			data = svgutil_skip_space(data);
			//','�Ȃ��΂�
			if (*data == ',') {
				data++;
				//,�̌�̋󔒂��΂�
				data = svgutil_skip_space(data);
			}
		}
		SVG_DPRINTF("\n");
	}

	return PARSED;
error:
	//�f�[�^�N���A����
	m_coords.clear();

	return PARSE_ERROR;
}

//�p�X�ɕϊ�
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
		cmd = SVG_CMD_L;	//�Q�߈ȍ~��LineTo
	}

	//Polyline�͕��Ȃ�

	return path;
}

