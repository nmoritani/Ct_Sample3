#ifndef _SVGRECT_H_
#define _SVGRECT_H_

#include "SvgObject.h"
#include "SvgPath.h"

class SvgRect : public SvgObject {
	typedef SvgObject	super;
public:

protected:
	float		m_x;
	float		m_y;
	float		m_width;
	float		m_height;
	float		m_rx;
	float		m_ry;
public:
	//コンストラクタ
	SvgRect(SvgParser *parser, SvgObject *parent)
		: SvgObject(parser, parent) {
		m_type = SVG_TYPE_RECT;
		//初期値設定
		m_x = 0.0f;
		m_y = 0.0f;
		m_rx = -1.0f;
		m_ry = -1.0f;
	}
	//デストラクタ
	virtual ~SvgRect();
	//属性解析
	virtual PARSE_RESULT parse_attribute(const char *att[]);
	//属性解析結果をチェック	
	virtual PARSE_RESULT parse_attribute_end();
	//パスに変換
	virtual SvgPath *cnv_to_path();
	//
	float x() const { return m_x; }
	float y() const { return m_y; }
	float width() const { return m_width; }
	float height() const { return m_height; }
	float rx() const { return m_rx; }
	float ry() const { return m_ry; }
};

#endif
