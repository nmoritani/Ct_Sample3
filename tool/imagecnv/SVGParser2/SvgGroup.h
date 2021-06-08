#ifndef _SVGGROUP_H_
#define _SVGGROUP_H_

#include "SvgObject.h"

class SvgParser;

class SvgGroup : public SvgObject {
	typedef SvgObject	super;
protected:
	SVGOBJECTLIST	m_objects;
public:
	//コンストラクタ
	SvgGroup(SvgParser *parser, SvgObject *parent);
	//デストラクタ
	virtual ~SvgGroup();
	//親オブジェクト取得 (SvgGroupにキャストするために作成)
	SvgGroup *parent() const {
		return (SvgGroup*)SvgObject::parent();
	}
	//オブジェクトリスト
	SVGOBJECTLIST *objects() { return &m_objects; }
	//オブジェクト追加
	void add(SvgObject *obj) {
		m_objects.push_back(obj);
	}
	//idからオブジェクトを検索
	SvgObject *find_object(const char *id);
	//オブジェクトを削除
	void delete_object(SvgObject *obj);
	//オブジェクトを削除
	void delete_all();
};

#endif
