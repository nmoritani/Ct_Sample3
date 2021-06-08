#ifndef _SVGCIRCLE_H_
#define _SVGCIRCLE_H_

#include "SvgObject.h"
#include "SvgPath.h"

class SvgCircle : public SvgObject {
	typedef SvgObject	super;
public:

protected:
	float		m_cx;
	float		m_cy;
	float		m_r;
public:
	//�R���X�g���N�^
	SvgCircle(SvgParser *parser, SvgObject *parent)
		: super(parser, parent) {
		m_type = SVG_TYPE_CIRCLE;
		//�����l�ݒ�
		m_cx = 0.0f;
		m_cy = 0.0f;
	}
	//�f�X�g���N�^
	virtual ~SvgCircle();
	//�������
	virtual PARSE_RESULT parse_attribute(const char *att[]);
	//�p�X�ɕϊ�
	virtual SvgPath *cnv_to_path();
	//
	float cx() const { return m_cx; }
	float cy() const { return m_cy; }
	float r() const { return m_r; }
};

#endif
