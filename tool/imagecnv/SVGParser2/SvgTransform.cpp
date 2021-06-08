#include "stdafx.h"
#include "SvgTransform.h"
#include "SvgUtil.h"

SvgTransform::SvgTransform(const SvgTransform *from)
{
	m_matrix[0][0] = from->m_matrix[0][0];
	m_matrix[0][1] = from->m_matrix[0][1];
	m_matrix[1][0] = from->m_matrix[1][0];
	m_matrix[1][1] = from->m_matrix[1][1];
	m_matrix[2][0] = from->m_matrix[2][0];
	m_matrix[2][1] = from->m_matrix[2][1];
}

PARSE_RESULT SvgTransform::parse(const char *attribute)
{
	PARSE_RESULT r;
	if (!strncmp(attribute, "translate", 9)) {
		r = parse_translate(attribute, &attribute);
		if (r != PARSED) {
			return r;
		}
	} else 
	if (!strncmp(attribute, "matrix", 6)) {
		r = parse_matrix(attribute, &attribute);
		if (r != PARSED) {
			return r;
		}
	} else 
	if (!strncmp(attribute, "scale", 5)) {
		r = parse_scale(attribute, &attribute);
		if (r != PARSED) {
			return r;
		}
	} else 
	{
		//Unknown
		fprintf(stderr, "Unknown transform value '%s'\n", attribute);
		return PARSE_ERROR;
	}
	//�󔒂��΂�
	attribute = svgutil_skip_space(attribute);
	//transform�������w�肳��Ă���ꍇ�͖��Ή��̂��߃G���[�Ƃ���
	if (*attribute != '\0') {
		return PARSE_ERROR;
	}

	return PARSED;
}

PARSE_RESULT SvgTransform::parse_translate(const char *attribute, const char **next_addr)
{
	float	x, y;

	//translate�̕������΂�
	attribute += 9;
	//'('��T��
	attribute = svgutil_skip_to_char(attribute, '(');
	//�󔒂��΂�
	attribute = svgutil_skip_space(attribute);
	//���l�ϊ�
	x = (float)strtod(attribute, (char**)&attribute);
	//���̐��l�܂Ŕ�΂�
	attribute = svgutil_skip_to_next_token(attribute);
	//���l�ϊ�
	y = (float)strtod(attribute, (char**)&attribute);
	//�󔒂��΂�
	attribute = svgutil_skip_space(attribute);
	//')'�`�F�b�N
	if (*attribute != ')') {
		return PARSE_ERROR;
	}
	//')'���΂�
	attribute++;
	//�s��ɐݒ�
	m_matrix[0][0] = 1;
	m_matrix[0][1] = 0;
	m_matrix[1][0] = 0;
	m_matrix[1][1] = 1;
	m_matrix[2][0] = x;
	m_matrix[2][1] = y;
	//
	SVG_DPRINTF("translae: %f, %f\n", x, y);
	//���̕����̏ꏊ��Ԃ�
	*next_addr = attribute;

	return PARSED;
}

PARSE_RESULT SvgTransform::parse_matrix(const char *attribute, const char **next_addr)
{
	int	line, column;

	//matrix�̕������΂�
	attribute += 6;
	//'('��T��
	attribute = svgutil_skip_to_char(attribute, '(');
	//�󔒂��΂�
	attribute = svgutil_skip_space(attribute);
	//�s��f�[�^�擾
	for (column = 0; column < 3; column++) {
		for (line = 0; line < 2; line++) {
			//���l�ϊ�
			m_matrix[column][line] = (float)strtod(attribute, (char**)&attribute);
			//���̐��l�܂Ŕ�΂�
			attribute = svgutil_skip_to_next_token(attribute);
		}
	}
	//')'�`�F�b�N
	if (*attribute != ')') {
		return PARSE_ERROR;
	}
	//')'���΂�
	attribute++;
	//
	SVG_DPRINTF("matrix: %f, %f, %f, %f, %f, %f\n",
				m_matrix[0][0], m_matrix[0][1], m_matrix[1][0], m_matrix[1][1], 
				m_matrix[2][0], m_matrix[2][1]);
	//���̕����̏ꏊ��Ԃ�
	*next_addr = attribute;

	return PARSED;
}

PARSE_RESULT SvgTransform::parse_scale(const char *attribute, const char **next_addr)
{
	float	x, y;

	//scale�̕������΂�
	attribute += 5;
	//'('��T��
	attribute = svgutil_skip_to_char(attribute, '(');
	//�󔒂��΂�
	attribute = svgutil_skip_space(attribute);
	//���l�ϊ�
	x = (float)strtod(attribute, (char**)&attribute);
	//���̐��l�܂Ŕ�΂�
	attribute = svgutil_skip_to_next_token(attribute);
	//���l�ϊ�
	y = (float)strtod(attribute, (char**)&attribute);
	//�󔒂��΂�
	attribute = svgutil_skip_space(attribute);
	//')'�`�F�b�N
	if (*attribute != ')') {
		return PARSE_ERROR;
	}
	//')'���΂�
	attribute++;
	//�s��ɐݒ�
	m_matrix[0][0] = x;
	m_matrix[0][1] = 0;
	m_matrix[1][0] = 0;
	m_matrix[1][1] = y;
	m_matrix[2][0] = 0;
	m_matrix[2][1] = 0;
	//
	SVG_DPRINTF("scale: %f, %f\n", x, y);
	//���̕����̏ꏊ��Ԃ�
	*next_addr = attribute;

	return PARSED;
}

/* �s��v�Z(�Q�����v�Z�ɓ���) */
inline static void matrix_mul(const float m1[3][2], const float m2[3][2], float out[3][2])
{
	out[0][0] = m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1];
	out[0][1] = m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1];
	out[1][0] = m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1];
	out[1][1] = m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1];
	out[2][0] = m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0];
	out[2][1] = m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1];
}

//�E����|����
void SvgTransform::mul(const SvgTransform *t)
{
	float	tmp[3][2];
	matrix_mul(m_matrix, t->m_matrix, tmp);		//arg1 * arg2 -> arg3
	memcpy(m_matrix, tmp, sizeof(m_matrix));
}

//���W�ϊ�
void SvgTransform::trans_xy(float x, float y, float *out_x, float *out_y) const
{
	*out_x = m_matrix[0][0] * x + m_matrix[1][0] * y + m_matrix[2][0];
	*out_y = m_matrix[0][1] * x + m_matrix[1][1] * y + m_matrix[2][1];
}

//�P���ϊ����ǂ�������
bool SvgTransform::is_identity() const
{
	if (m_matrix[0][0] == 1.0f && m_matrix[1][0] == 0.0f && m_matrix[2][0] == 0.0f && 
		m_matrix[0][1] == 0.0f && m_matrix[1][1] == 1.0f && m_matrix[2][1] == 0.0f) {
		return true;
	}

	return false;
}


//�f�o�b�O�\��
void SvgTransform::debug_print()
{
#if SVGDEBUGOUT
	SVG_DPRINTF(" %f, %f %f\n", m_matrix[0][0], m_matrix[1][0], m_matrix[2][0]);
	SVG_DPRINTF(" %f, %f %f\n", m_matrix[0][1], m_matrix[1][1], m_matrix[2][1]);
#endif
}

