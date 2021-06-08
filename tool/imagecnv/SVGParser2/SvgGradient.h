#ifndef _SVGGRADIENT_H_
#define _SVGGRADIENT_H_

#include "SvgObject.h"
#include "SvgGroup.h"
#include "SvgStop.h"

class SvgGradient : public SvgGroup {
	typedef SvgGroup	super;
public:

protected:
	SVGSTOPS			m_stops;
	SvgGradient			*m_ref_obj;
public:
	//コンストラクタ
	SvgGradient(SvgParser *parser, SvgObject *parent);
	//デストラクタ
	virtual ~SvgGradient();
	//属性解析
	virtual PARSE_RESULT parse_attribute(const char *att[]);
	//stop追加
	void add_stop(SvgStop *stop) {
		m_stops.push_back(stop);
	}
	//
	const SVGSTOPS *stops() const { return &m_stops; }
	//参照先も含めてstop情報を探す
	const SVGSTOPS *find_stops() const {
		if (m_stops.size() == 0) {
			if (m_ref_obj != NULL) {
				return m_ref_obj->find_stops();
			} else {
				return NULL;
			}
		} else {
			return &m_stops;
		}
	}
	const SvgGradient *ref_obj() const { return m_ref_obj; }
};

#endif
