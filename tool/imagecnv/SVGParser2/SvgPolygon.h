#ifndef _SVGPOLYGON_H_
#define _SVGPOLYGON_H_

#include "SvgObject.h"
#include "SvgPath.h"

class SvgPolygon : public SvgObject {
	typedef SvgObject	super;
public:

protected:
	SVGCOORDS	m_coords;
public:
	//コンストラクタ
	SvgPolygon(SvgParser *parser, SvgObject *parent)
		: SvgObject(parser, parent) {
		m_type = SVG_TYPE_POLYGON;
	}
	//デストラクタ
	virtual ~SvgPolygon();
	//属性解析
	virtual PARSE_RESULT parse_attribute(const char *att[]);
	//座標データ解析
	PARSE_RESULT SvgPolygon::parse_points(const char *data);
	//パスに変換
	virtual SvgPath *cnv_to_path();
	//
	const SVGCOORDS *coords() const {return &m_coords; }
};

#endif
