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
	//コンストラクタ
	SvgStop(SvgParser *parser, SvgObject *parent);
	//デストラクタ
	virtual ~SvgStop();
	//属性解析
	virtual PARSE_RESULT parse_attribute(const char *att[]);
	//
	float offset() const { return m_offset; }
};

#endif
