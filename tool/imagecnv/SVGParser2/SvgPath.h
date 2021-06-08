#ifndef _SVGPATH_H_
#define _SVGPATH_H_

#include "SvgObject.h"

class SvgPath : public SvgObject {
	typedef SvgObject	super;
public:

protected:
	SVGCMDS			m_commands;
	SVGCOORDS		m_coords;
public:
	//コンストラクタ
	SvgPath(SvgParser *parser, SvgObject *parent)
		: SvgObject(parser, parent) {
		m_type = SVG_TYPE_PATH;
	}
	//コンストラクタ(パス変換用)	//元オブジェクトの情報をコピーする
	SvgPath(SvgObject *src)
		: SvgObject(src) {
		m_type = SVG_TYPE_PATH;
	}
	//デストラクタ
	virtual ~SvgPath();
	//属性解析
	virtual PARSE_RESULT parse_attribute(const char *att[]);
	//パスデータ解析
	PARSE_RESULT parse_d(const char *data);
	//コマンド追加
	void add_command(SVG_CMD cmd) {
		m_commands.push_back(cmd);
	}
	//座標追加
	void add_coord(float coord) {
		m_coords.push_back(coord);
	}
	//
	const SVGCOORDS *coords() const {return &m_coords; }
	const SVGCMDS *commands() const {return &m_commands; }
};

#endif
