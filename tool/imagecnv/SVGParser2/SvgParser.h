#ifndef _SVGPARSER_H_
#define _SVGPARSER_H_

#include "SvgCircle.h"
#include "SvgEllipse.h"
#include "SvgGroup.h"
#include "SvgSVg.h"
#include "SvgLine.h"
#include "SvgLinearGradient.h"
#include "SvgRadialGradient.h"
#include "SvgPath.h"
#include "SvgPolygon.h"
#include "SvgPolyline.h"
#include "SvgRect.h"

class SvgParser {
public:

protected:
	int				m_error;
	SvgGroup		m_defs;			//定義
	SvgSvg			*m_root;		//ルート
	int				m_depth;		//ネスト
	int				m_skip_depth;	//スキップしているエレメントのネスト
	SvgGroup		*m_current;		//カレントグループ
	bool			m_is_parse_style;	// スタイルのパース中か否か
	SVGSTYLEMAP     m_styles;			// スタイル定義マップ
public:
	//コンストラクタ
	SvgParser();
	//デストラクタ
	~SvgParser();
	//エラーコード設定
	void set_error(int err) { m_error = err; }
	//エラーコード取得
	int error() const { return m_error; }
	//解析
	int parse(const char *filename);
	//defs
	SvgGroup *defs() { return &m_defs; }
	//ルートグループ
	SvgSvg *root() { return m_root; }
	//idから定義を検索
	SvgObject *find_defs(const char *id) {
		return m_defs.find_object(id);
	}
	//定義を削除	(SvgLinearGradientのマージに使用)
	void delete_defs(SvgObject *obj) {
		m_defs.delete_object(obj);
	}
	// class名からスタイルを検索
	SvgStyle *find_style_by_class(const char *name);

	/* XMLパーサー用 */
	//XMLエレメント開始
	void element_start(const char *name, const char *atts[]);
	//XMLエレメント終了
	void element_end(const char *name);
	//スタイル文字列処理
	void charcter_data(const char* c, int len);
};

#endif
