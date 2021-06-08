#ifndef _SVGLINEARGRADIENT_H_
#define _SVGLINEARGRADIENT_H_

#include "SvgObject.h"
#include "SvgGradient.h"
#include "SvgStop.h"

class SvgLinearGradient : public SvgGradient {
	typedef SvgGradient	super;
public:

protected:
	float				m_x1;
	float				m_y1;
	float				m_x2;
	float				m_y2;
public:
	//コンストラクタ
	SvgLinearGradient(SvgParser *parser, SvgObject *parent);
	//デストラクタ
	virtual ~SvgLinearGradient();
	//属性解析
	virtual PARSE_RESULT parse_attribute(const char *att[]);
	//
	float x1() const { return m_x1; }
	float y1() const { return m_y1; }
	float x2() const { return m_x2; }
	float y2() const { return m_y2; }
};

#endif
