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
	//コンストラクタ
	SvgRadialGradient(SvgParser *parser, SvgObject *parent);
	//デストラクタ
	virtual ~SvgRadialGradient();
	//属性解析
	virtual PARSE_RESULT parse_attribute(const char *att[]);
	//属性解析結果をチェック
	virtual PARSE_RESULT parse_attribute_end();
	//
	float cx() const { return m_cx; }
	float cy() const { return m_cy; }
	float fx() const { return m_fx; }
	float fy() const { return m_fy; }
	float r()  const { return m_r; }
};

#endif
