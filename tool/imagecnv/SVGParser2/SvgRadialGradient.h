#ifndef _SVGRADIALGRADIENT_H_
#define _SVGRADIALGRADIENT_H_

#include "SvgObject.h"
#include "SvgGradient.h"
#include "SvgStop.h"

class SvgRadialGradient : public SvgGradient {
	typedef SvgGradient	super;
public:

protected:
	float				m_cx;
	float				m_cy;
	float				m_fx;
	float				m_fy;
	float				m_r;
public:
	//�R���X�g���N�^
	SvgRadialGradient(SvgParser *parser, SvgObject *parent);
	//�f�X�g���N�^
	virtual ~SvgRadialGradient();
	//�������
	virtual PARSE_RESULT parse_attribute(const char *att[]);
	//������͌��ʂ��`�F�b�N
	virtual PARSE_RESULT parse_attribute_end();
	//
	float cx() const { return m_cx; }
	float cy() const { return m_cy; }
	float fx() const { return m_fx; }
	float fy() const { return m_fy; }
	float r()  const { return m_r; }
};

#endif
