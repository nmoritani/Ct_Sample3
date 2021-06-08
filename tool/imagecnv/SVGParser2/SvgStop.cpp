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

//�������
PARSE_RESULT SvgStop::parse_attribute(const char *att[])
{
	if (!strcmp(att[0], "offset")) {
		//offset
		m_offset = (float)atof(att[1]);
		SVG_DPRINTF("offset=%f\n", m_offset);
		return PARSED;
	} else
	{
		//�X�[�p�[�N���X�̃��\�b�h�Ăяo��
		return super::parse_attribute(att);
	}
}


