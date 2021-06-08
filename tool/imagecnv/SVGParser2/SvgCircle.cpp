#include "stdafx.h"
#include "SvgCircle.h"

//�f�X�g���N�^
SvgCircle::~SvgCircle()
{
}

//�������
PARSE_RESULT SvgCircle::parse_attribute(const char *att[])
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
	if (!strcmp(att[0], "r")) {
		//r
		m_r = (float)atof(att[1]);
		return PARSED;
	} else
	{
		//�X�[�p�[�N���X�̃��\�b�h�Ăяo��
		return super::parse_attribute(att);
	}
}

//�p�X�ɕϊ�
SvgPath *SvgCircle::cnv_to_path()
{
	SvgPath		*path = NEW SvgPath(this);

	float x1, x2, x3;
	float y1, y2, y3;
	float clen;			//����_�܂ł̒���
	float cx1, cx2, cy1, cy2;
	//�悭�g�����W���Ɍv�Z
	x1 = m_cx - m_r;
	x2 = m_cx;
	x3 = m_cx + m_r;
	y1 = m_cy - m_r;
	y2 = m_cy;
	y3 = m_cy+ m_r;
	clen = svgutil_bezier_control_point(m_r);
	cx1 = x2 - clen;
	cx2 = x2 + clen;
	cy1 = y2 - clen;
	cy2 = y2 + clen;
	//Move
	path->add_command(SVG_CMD_M);
	path->add_coord(x1);
	path->add_coord(y2);
	//Curve
	path->add_command(SVG_CMD_C);
	path->add_coord(x1);
	path->add_coord(cy1);
	path->add_coord(cx1);
	path->add_coord(y1);
	path->add_coord(x2);
	path->add_coord(y1);
	//Curve
	path->add_command(SVG_CMD_C);
	path->add_coord(cx2);
	path->add_coord(y1);
	path->add_coord(x3);
	path->add_coord(cy1);
	path->add_coord(x3);
	path->add_coord(y2);
	//Curve
	path->add_command(SVG_CMD_C);
	path->add_coord(x3);
	path->add_coord(cy2);
	path->add_coord(cx2);
	path->add_coord(y3);
	path->add_coord(x2);
	path->add_coord(y3);
	//Curve
	path->add_command(SVG_CMD_C);
	path->add_coord(cx1);
	path->add_coord(y3);
	path->add_coord(x1);
	path->add_coord(cy2);
	path->add_coord(x1);
	path->add_coord(y2);
	//Close
	path->add_command(SVG_CMD_z);

	return path;
}



