#ifndef _SVGSTOP_H_
#define _SVGSTOP_H_

#include "SvgObject.h"
#include "SvgStop.h"

class SvgStop : public SvgObject {
	typedef SvgObject	super;
public:

protected:
	float					m_offset;
public:
	//�R���X�g���N�^
	SvgStop(SvgParser *parser, SvgObject *parent);
	//�f�X�g���N�^
	virtual ~SvgStop();
	//�������
	virtual PARSE_RESULT parse_attribute(const char *att[]);
	//
	float offset() const { return m_offset; }
};

#endif
