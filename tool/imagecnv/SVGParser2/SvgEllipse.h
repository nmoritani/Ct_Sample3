#ifndef _SVGELLIPSE_H_
#define _SVGELLIPSE_H_

#include "SvgObject.h"
#include "SvgPath.h"

class SvgEllipse : public SvgObject {
	typedef SvgObject	super;
public:

protected:
	float		m_cx;
	float		m_cy;
	float		m_rx;
	float		m_ry;
public:
	//�R���X�g���N�^
	SvgEllipse(SvgParser *parser, SvgObject *parent)
		: super(parser, parent) {
		m_type = SVG_TYPE_ELLIPSE;
		//�����l�ݒ�
		m_cx = 0.0f;
		m_cy = 0.0f;
	}
	//�f�X�g���N�^
	virtual ~SvgEllipse();
	//�������
	virtual PARSE_RESULT parse_attribute(const char *att[]);
	//�p�X�ɕϊ�
	virtual SvgPath *cnv_to_path();
	//
	float cx() const { return m_cx; }
	float cy() const { return m_cy; }
	float rx() const { return m_rx; }
	float ry() const { return m_ry; }
};

#endif
