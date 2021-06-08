#ifndef _SVGLINE_H_
#define _SVGLINE_H_

#include "SvgObject.h"
#include "SvgPath.h"

class SvgLine : public SvgObject {
	typedef SvgObject	super;
public:

protected:
	float		m_x1;
	float		m_y1;
	float		m_x2;
	float		m_y2;
public:
	//コンストラクタ
	SvgLine(SvgParser *parser, SvgObject *parent)
		: super(parser, parent) {
		m_type = SVG_TYPE_LINE;
		//初期値設定
		m_x1 = 0.0f;
		m_y1 = 0.0f;
		m_x2 = 0.0f;
		m_y2 = 0.0f;
	}

	//デストラクタ
	virtual ~SvgLine();
	//属性解析
	virtual PARSE_RESULT parse_attribute(const char *att[]);
	//パスに変換
	virtual SvgPath *cnv_to_path();
	//
	float x1() const { return m_x1; }
	float y1() const { return m_y1; }
	float x2() const { return m_x2; }
	float y2() const { return m_y2; }
};

#endif
