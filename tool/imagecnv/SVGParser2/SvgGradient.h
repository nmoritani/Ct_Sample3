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
	//�R���X�g���N�^
	SvgGradient(SvgParser *parser, SvgObject *parent);
	//�f�X�g���N�^
	virtual ~SvgGradient();
	//�������
	virtual PARSE_RESULT parse_attribute(const char *att[]);
	//stop�ǉ�
	void add_stop(SvgStop *stop) {
		m_stops.push_back(stop);
	}
	//
	const SVGSTOPS *stops() const { return &m_stops; }
	//�Q�Ɛ���܂߂�stop����T��
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
