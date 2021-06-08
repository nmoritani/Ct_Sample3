#include "stdafx.h"
#include "string.h"
#include "expat.h"
#include "SvgParser.h"
#include "SvgUtil.h"
#include "SvgStyle.h"

static void handler_element_start(void *userData, const XML_Char *name, const XML_Char *atts[]);
static void handler_element_end(void *userData, const XML_Char *name);
static void handler_character_data(void *userData, const XML_Char *s, int len);

SvgParser::SvgParser()
	: m_defs(NULL, NULL)
{
	m_error = 0;	//エラークリア
	m_depth = 1;
	m_skip_depth = 0;
	m_root = NULL;
	m_current = NULL;
	m_is_parse_style = false;
}

SvgParser::~SvgParser()
{
	delete(m_root);

	if (!m_styles.empty()) {
		for( SVGSTYLEMAP::iterator itr = m_styles.begin(); itr != m_styles.end(); ++itr ) {
			delete itr->second;
		}
	}
}

int SvgParser::parse(const char *filename)
{
	FILE			*fp;
	fpos_t			fsize;
	size_t			bufsize;
	char			*buf;
	XML_Parser		parser;
	XML_Status		xmlerr;

	//ファイルオープン
	fp = fopen(filename, "rb");
	if (fp == NULL) {
		fprintf(stderr, "ERROR: File Not Found %s\n", filename);
		return -1;
	}

	//ファイルサイズ
	fseek(fp, 0, SEEK_END); 
	fgetpos(fp, &fsize);
	fseek(fp, 0, SEEK_SET); 

	//メモリに読み込み
	bufsize = (size_t)fsize;
	buf = (char *)malloc(bufsize);
	fread(buf, 1, bufsize, fp);

	//ファイルクローズ
	fclose(fp);

	//パーサー初期化
	parser = XML_ParserCreate(NULL);
	if (parser == NULL) {
		fprintf(stderr, "ERROR: Create Parser Error\n");
		return -1;
	}
	//ユーザーデータにthis設定
	XML_SetUserData(parser, this);
	//ハンドラ設定
	XML_SetElementHandler(parser, handler_element_start, handler_element_end);
	XML_SetCharacterDataHandler(parser, handler_character_data);

	//パース
	xmlerr = XML_Parse(parser, buf, (int)bufsize, 1);

	//パーサー削除
	XML_ParserFree(parser);

	//メモリ解放
	free(buf);

	if (xmlerr != XML_STATUS_OK) {
		fprintf(stderr, "ERROR: Parse Xml Error\n");
		return -1;
	}

	if (m_error != 0) {
		fprintf(stderr, "ERROR: Parse Error\n");
		return -1;
	}

	return 0;
}

static void handler_element_start(void *userData, const XML_Char *name, const XML_Char *atts[])
{
	SvgParser *p = (SvgParser*)userData;
	p->element_start(name, atts);
}

static void handler_element_end(void *userData, const XML_Char *name)
{
	SvgParser *p = (SvgParser*)userData;
	p->element_end(name);
}

void SvgParser::element_start(const char *name, const char *atts[])
{
	if (m_skip_depth == 0) {
		//svgエレメント
		if (!strcmp(name, "svg")) {
			//svg
			SVG_DPRINTF("<svg>\n");
			SvgSvg *obj = NEW SvgSvg(this, m_current);
			//属性解析
			obj->parse_atts(atts);
			//ルートに設定
			m_root = obj;
			//カレントグループ更新
			m_current = obj;
		} else
		//defsエレメント
		if (!strcmp(name, "defs")) {
			//defs
			SVG_DPRINTF("<defs>\n");
			m_defs.set_parent(m_current);
			m_current = &m_defs;		//定義はm_defsに追加する defsがネストされているとNG
		} else
		//gエレメント
		if (!strcmp(name, "g")) {
			//g
			SVG_DPRINTF("<g>\n");
			SvgGroup *obj = NEW SvgGroup(this, m_current);
			//属性解析
			obj->parse_atts(atts);
			//カレントグループに追加
			m_current->add(obj);
			//カレントグループ更新
			m_current = obj;
		} else
		//circleエレメント
		if (!strcmp(name, "circle")) {
			//circle
			SVG_DPRINTF("<circle>\n");
			SvgCircle *obj = NEW SvgCircle(this, m_current);
			//属性解析
			obj->parse_atts(atts);
			//カレントグループに追加
			m_current->add(obj);
			//currentに設定しないのでelement_endで階層が戻らないようにスキップ設定しておく
			m_skip_depth = m_depth;
		} else
		//ellipseエレメント
		if (!strcmp(name, "ellipse")) {
			//ellipse
			SVG_DPRINTF("<ellipse>\n");
			SvgEllipse *obj = NEW SvgEllipse(this, m_current);
			//属性解析
			obj->parse_atts(atts);
			//カレントグループに追加
			m_current->add(obj);
			//currentに設定しないのでelement_endで階層が戻らないようにスキップ設定しておく
			m_skip_depth = m_depth;
		} else
		//lineエレメント
		if (!strcmp(name, "line")) {
			//ellipse
			SVG_DPRINTF("<line>\n");
			SvgLine *obj = NEW SvgLine(this, m_current);
			//属性解析
			obj->parse_atts(atts);
			//カレントグループに追加
			m_current->add(obj);
			//currentに設定しないのでelement_endで階層が戻らないようにスキップ設定しておく
			m_skip_depth = m_depth;
		} else
		//pathエレメント
		if (!strcmp(name, "path")) {
			//path
			SVG_DPRINTF("<path>\n");
			SvgPath *obj = NEW SvgPath(this, m_current);
			//属性解析
			obj->parse_atts(atts);
			//カレントグループに追加
			m_current->add(obj);
			//currentに設定しないのでelement_endで階層が戻らないようにスキップ設定しておく
			m_skip_depth = m_depth;
		} else
		//polygonエレメント
		if (!strcmp(name, "polygon")) {
			//polygon
			SVG_DPRINTF("<polygon>\n");
			SvgPolygon *obj = NEW SvgPolygon(this, m_current);
			//属性解析
			obj->parse_atts(atts);
			//カレントグループに追加
			m_current->add(obj);
			//currentに設定しないのでelement_endで階層が戻らないようにスキップ設定しておく
			m_skip_depth = m_depth;
		} else
		//polylineエレメント
		if (!strcmp(name, "polyline")) {
			//polygon
			SVG_DPRINTF("<polyline>\n");
			SvgPolyline *obj = NEW SvgPolyline(this, m_current);
			//属性解析
			obj->parse_atts(atts);
			//カレントグループに追加
			m_current->add(obj);
			//currentに設定しないのでelement_endで階層が戻らないようにスキップ設定しておく
			m_skip_depth = m_depth;
		} else
		//rectエレメント
		if (!strcmp(name, "rect")) {
			//rect
			SVG_DPRINTF("<rect>\n");
			SvgRect *obj = NEW SvgRect(this, m_current);
			//属性解析
			obj->parse_atts(atts);
			//カレントグループに追加
			m_current->add(obj);
			//currentに設定しないのでelement_endで階層が戻らないようにスキップ設定しておく
			m_skip_depth = m_depth;
		} else
		//linearGradientエレメント
		if (!strcmp(name, "linearGradient")) {
			//linearGradient
			SVG_DPRINTF("<linearGradient>\n");
			SvgLinearGradient *obj = NEW SvgLinearGradient(this, m_current);
			//属性解析
			obj->parse_atts(atts);
			//defsに追加する
			//本来ならカレントグループに追加するべきだけどdefsにまとまっている方が検索しやすいのでこうする
			m_defs.add(obj);
			//カレントグループ更新
			m_current = obj;
		} else
		//radialGradientエレメント
		if (!strcmp(name, "radialGradient")) {
			//radialGradient
			SVG_DPRINTF("<radialGradient>\n");
			SvgRadialGradient *obj = NEW SvgRadialGradient(this, m_current);
			//属性解析
			obj->parse_atts(atts);
			//defsに追加する
			//本来ならカレントグループに追加するべきだけどdefsにまとまっている方が検索しやすいのでこうする
			m_defs.add(obj);
			//カレントグループ更新
			m_current = obj;
		} else
		//stopエレメント
		if (!strcmp(name, "stop")) {
			//stop
			SVG_DPRINTF("<stop>\n");
			//親がグラデーションの場合だけ解析
			SvgGradient *gradient = dynamic_cast<SvgGradient*>(m_current);
			if (gradient != NULL) {
				SvgStop *obj = NEW SvgStop(this, m_current);
				//属性解析
				obj->parse_atts(atts);
				gradient->add_stop(obj);
			}
			//currentに設定しないのでelement_endで階層が戻らないようにスキップ設定しておく
			m_skip_depth = m_depth;
		} else
		// styleエレメント
		if (!strcmp(name, "style")) {
			//style
			SVG_DPRINTF("<style>\n");
			// スタイルタグ内のみスタイルパースを行う
			m_is_parse_style = true;
			m_skip_depth = m_depth;
		} else
		{
			//その他
			SVG_DPRINTF("<%s>\n", name);
			SVG_DPRINTF("  ignore internal elements...\n");
			//スキップ
			m_skip_depth = m_depth;
		}
	}
	//ネストを増やす
	m_depth++;
}

void SvgParser::element_end(const char *name)
{
	//ネストを減らす
	m_depth--;

	if (strcmp(name, "style") == 0) {
		// スタイルタグ外はスタイルパースを行わない
		m_is_parse_style = false;
	}
	
	if (m_skip_depth == 0) {
		SVG_DPRINTF("</%s>\n", name);
		m_current = m_current->parent();
	} else {
		if (m_skip_depth == m_depth) {
			SVG_DPRINTF("</%s>\n", name);
			m_skip_depth = 0;
		}
	}
}

static void handler_character_data(void *userData, const XML_Char *s, int len)
{
	SvgParser *p = (SvgParser*)userData;
	p->charcter_data(s,len);
}

void SvgParser::charcter_data(const char* c, int len)
{
	// 改行文字スキップ
	if (len==1 && c[0]==0x0a) return;

	// タブ文字スキップ
	if (c[0] == '\t'){
		c++;
		len--;
	}

	if ( m_is_parse_style ) {
		SVG_DPRINTF("handler_SetCharacterData(On)\n");

		// [.クラス名]指定のみ対応
		// [#id名]指定や[要素名]指定等には非対応
		// また、複数行のスタイル定義にも非対応
		string line(c, c+len);
		string class_name = line.substr(0, line.find("{"));		// '.'から'{'がclass名
		string style_def  = line.substr(line.find("{") + 1);	// '{'から'}'がスタイル定義
		style_def.erase(style_def.end()-1);
		
		SvgStyle *style = new SvgStyle();
		style->parse_style(this, m_current->parent(), style_def.c_str());
		
		// スタイルを保存
		m_styles[class_name] = style;
	}
}

SvgStyle *SvgParser::find_style_by_class(const char *name) {
	string class_name(name);
	class_name = "." + class_name;
	
	if (m_styles.count(class_name) > 0 ) {
		return m_styles[class_name];
	}

	return NULL;
}
