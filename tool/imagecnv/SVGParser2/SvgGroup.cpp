#include "stdafx.h"
#include "SvgGroup.h"
#include "SvgUtil.h"
#include <algorithm>

SvgGroup::SvgGroup(SvgParser *parser, SvgObject *parent)
	: SvgObject(parser, parent)
{
	m_type = SVG_TYPE_GROUP;
}

SvgGroup::~SvgGroup()
{
	delete_all();
}

//idからオブジェクトを検索
SvgObject *SvgGroup::find_object(const char *id)
{
	SVGOBJECTLIST::iterator i;

	for (i = m_objects.begin(); i != m_objects.end(); ++i) {
		if ((*i)->id()->compare(id) == 0) {
			return *i;
		}
	}
	return NULL;
}

//オブジェクトを削除
void SvgGroup::delete_object(SvgObject *obj)
{
	SVGOBJECTLIST::iterator i;

	for (i = m_objects.begin(); i != m_objects.end(); ++i) {
		if (*i == obj) {
			m_objects.erase(i);
			delete obj;
			break;
		}
	}
}


void SvgGroup::delete_all()
{
	SVGOBJECTLIST::iterator i;

	for (i = m_objects.begin(); i != m_objects.end(); ++i) {
		delete *i;
	}

	m_objects.clear();
}


