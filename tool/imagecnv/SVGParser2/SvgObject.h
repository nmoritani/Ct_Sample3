#ifndef _SVGOBJECT_H_
#define _SVGOBJECT_H_

#include "SvgTransform.h"
#include "SvgStyle.h"
#include "SvgUtil.h"

extern int	g_SVGPARSER_COMPATIBLE_GENSKETCH_EVENODD;				//デフォルトをEVEN_ODDにする

typedef enum {
	//図形
	SVG_TYPE_PATH,
	SVG_TYPE_POLYGON,
	SVG_TYPE_POLYLINE,
	SVG_TYPE_CIRCLE,
	SVG_TYPE_ELLIPSE,
	SVG_TYPE_ROUNDRECT,
	SVG_TYPE_RECT,
	SVG_TYPE_LINE,
	SVG_TYPE_FIGURE_END,
	//図形以外
	SVG_TYPE_SVG,
	SVG_TYPE_GROUP,
	SVG_TYPE_GRADIENT,
	SVG_TYPE_LINEARGRADIENT,
	SVG_TYPE_RADIALGRADIENT,
	SVG_TYPE_STOP,
	SVG_TYPE_TYPE_MAX
} SVG_OBJECT_TYPE;

class SvgParser;
class SvgPath;

class SvgObject {
public:
	SVG_OBJECT_TYPE	m_type;
	int				m_ref_count;
	SvgObject		*m_referred_object;
	SvgParser		*m_parser;
	SvgObject		*m_parent;
	SvgTransform	*m_transform;
	SvgTransform	*m_abs_transform;
	SvgStyle		m_style;
	string			m_id;		//id属性:※Gradient以外ではパースしていない
	unsigned long	m_user_data;
protected:

public:
	//コンストラクタ
	SvgObject(SvgParser *parser, SvgObject *parent);
	//コンストラクタ(パス変換時専用：parser,parent,transform,abs_transform,user_dataをコピー)
	SvgObject(SvgObject *src);
	//デストラクタ
	virtual ~SvgObject();
	//属性の配列解析
	PARSE_RESULT parse_atts(const char *atts[]);
	//属性解析
	virtual PARSE_RESULT parse_attribute(const char *att[]);
	//属性解析結果をチェック
	virtual PARSE_RESULT parse_attribute_end();
	//親オブジェクト設定
	void set_parent(SvgObject *parent) {
		m_parent = parent;
	}
	//パーサーオブジェクト取得
	SvgParser *parser() const {
		return m_parser;
	}
	//親オブジェクト取得
	SvgObject *parent() const {
		return m_parent;
	}
	//type取得
	SVG_OBJECT_TYPE type() const { return m_type; }
	//id取得
	const string* id() const { return &m_id; }
	//参照カウンタ++
	void add_ref_count() { m_ref_count++; }
	//参照カウンタ--
	void sub_ref_count() { m_ref_count--; }
	//参照カウンタ取得
	int ref_count() const { return m_ref_count; }
	//参照元オブジェクト設定
	void set_referred_object(SvgObject *obj) { m_referred_object = obj; }
	//参照元オブジェクト取得
	const SvgObject *referred_object() const { return m_referred_object; }
	//ユーザーデータ設定
	void set_user_data(unsigned long data) { m_user_data = data; }
	//ユーザーデータ取得
	unsigned long user_data() const { return m_user_data; }
	//transform取得
	const SvgTransform *transform() const { return m_transform; }
	const SvgTransform *abs_transform() const { return m_abs_transform; }
	//スタイル取得
	const SvgStyle *style() const { return &m_style; }
	//パスに変換
	virtual SvgPath *cnv_to_path();

};

#endif
