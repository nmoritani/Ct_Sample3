#ifndef _SVGTRANSFORM_H_
#define _SVGTRANSFORM_H_

#include "SvgUtil.h"

class SvgTransform {
friend SvgTransform;
public:
protected:
	float	m_matrix[3][2];		//�Q�����ϊ��p�̕ϊ��s��	matrix[��index][�cindex]
public:
	//�R���X�g���N�^
	SvgTransform() {};
	SvgTransform(const SvgTransform *from);
	//���
	PARSE_RESULT parse(const char *attribute);
	//��Z�H
	void mul(const SvgTransform *t);
	//���W�ϊ�
	void trans_xy(float x, float y, float *out_x, float *out_y) const;
	//�P���ϊ����ǂ�������
	bool is_identity() const;
	//�f�o�b�O�\��
	void debug_print();
protected:
	//translate(x,y)�̉��
	PARSE_RESULT parse_translate(const char *attribute, const char **next_addr);
	//matrix(f,f,f,f,f,f)�̉��
	PARSE_RESULT parse_matrix(const char *attribute, const char **next_addr);
	//scale(x,y)�̉��
	PARSE_RESULT parse_scale(const char *attribute, const char **next_addr);

};

#endif
