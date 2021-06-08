#include "stdafx.h"
#include "SvgRect.h"

//�f�X�g���N�^
SvgRect::~SvgRect()
{
}

//�������
PARSE_RESULT SvgRect::parse_attribute(const char *att[])
{
	if (!strcmp(att[0], "x")) {
		//x
		m_x = (float)atof(att[1]);
		return PARSED;
	} else
	if (!strcmp(att[0], "y")) {
		//y
		m_y = (float)atof(att[1]);
		return PARSED;
	} else
	if (!strcmp(att[0], "width")) {
		//width
		m_width = (float)atof(att[1]);
		return PARSED;
	} else
	if (!strcmp(att[0], "height")) {
		//height
		m_height = (float)atof(att[1]);
		return PARSED;
	} else
	if (!strcmp(att[0], "rx")) {
		//rx
		float tmp_rx;
		tmp_rx = (float)atof(att[1]);
		if( tmp_rx < 0) {
			//��͌��ʂ����̒l�Ȃ�΁A�G���[�Ƃ���B
			return PARSE_ERROR;
		}
		m_rx = tmp_rx;
		return PARSED;
	} else
	if (!strcmp(att[0], "ry")) {
		//ry
		float tmp_ry;
		tmp_ry = (float)atof(att[1]);
		if( tmp_ry < 0) {
			//��͌��ʂ����̒l�Ȃ�΁A�G���[�Ƃ���B
			return PARSE_ERROR;
		}
		m_ry = tmp_ry;
		return PARSED;
	} else
	{
		//�X�[�p�[�N���X�̃��\�b�h�Ăяo��
		return super::parse_attribute(att);
	}
}

PARSE_RESULT SvgRect::parse_attribute_end()
{
	//m_rx,m_ry���s���Ȓl�������ꍇ�A�␳����B
	if(m_rx == -1 && m_ry == -1){
		//m_rx,m_ry�������́˒��p
		m_rx = 0;
		m_ry = 0;
	} else if(m_rx == -1) {
		//m_rx�������́�m_ry�ɍ��킹��
		m_rx = m_ry;
	} else if(m_ry == -1) {
		//m_ry�������́�rx�ɍ��킹��
		m_ry = m_rx;
	}
	
	return PARSED;
}



//�p�X�ɕϊ�
SvgPath *SvgRect::cnv_to_path()
{
	SvgPath		*path = NEW SvgPath(this);

	//����p���玞�v���ɕϊ�
	if (m_rx != 0 || m_ry != 0) {
		//�p�ۋ�`
		float x1, x2, x3, x4;
		float y1, y2, y3, y4;
		float cx, cy;		//����_�܂ł̒���
		float cx1, cx2, cy1, cy2;
		//�悭�g�����W���Ɍv�Z
		x1 = m_x;
		x2 = m_x + m_rx;
		x3 = m_x + m_width - m_rx;
		x4 = m_x + m_width;
		y1 = m_y;
		y2 = m_y + m_ry;
		y3 = m_y + m_height - m_ry;
		y4 = m_y + m_height;
		cx = svgutil_bezier_control_point(m_rx);
		cy = svgutil_bezier_control_point(m_ry);
		cx1 = x2 - cx;
		cx2 = x3 + cx;
		cy1 = y2 - cy;
		cy2 = y3 + cy;
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
		//H Line
		path->add_command(SVG_CMD_H);
		path->add_coord(x3);
		//Curve
		path->add_command(SVG_CMD_C);
		path->add_coord(cx2);
		path->add_coord(y1);
		path->add_coord(x4);
		path->add_coord(cy1);
		path->add_coord(x4);
		path->add_coord(y2);
		//V Line
		path->add_command(SVG_CMD_V);
		path->add_coord(y3);
		//Curve
		path->add_command(SVG_CMD_C);
		path->add_coord(x4);
		path->add_coord(cy2);
		path->add_coord(cx2);
		path->add_coord(y4);
		path->add_coord(x3);
		path->add_coord(y4);
		//H Line
		path->add_command(SVG_CMD_H);
		path->add_coord(x2);
		//Curve
		path->add_command(SVG_CMD_C);
		path->add_coord(cx1);
		path->add_coord(y4);
		path->add_coord(x1);
		path->add_coord(cy2);
		path->add_coord(x1);
		path->add_coord(y3);
		//Close
		path->add_command(SVG_CMD_z);
	} else {
		//��`
		//Move
		path->add_command(SVG_CMD_M);
		path->add_coord(m_x);
		path->add_coord(m_y);
		//H Line
		path->add_command(SVG_CMD_H);
		path->add_coord(m_x + m_width);
		//V Line
		path->add_command(SVG_CMD_V);
		path->add_coord(m_y + m_height);
		//H Line
		path->add_command(SVG_CMD_H);
		path->add_coord(m_x);
		//Close
		path->add_command(SVG_CMD_z);
	}

	return path;
}

