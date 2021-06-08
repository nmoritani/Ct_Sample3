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
	//�R���X�g���N�^
	SvgPolygon(SvgParser *parser, SvgObject *parent)
		: SvgObject(parser, parent) {
		m_type = SVG_TYPE_POLYGON;
	}
	//�f�X�g���N�^
	virtual ~SvgPolygon();
	//�������
	virtual PARSE_RESULT parse_attribute(const char *att[]);
	//���W�f�[�^���
	PARSE_RESULT SvgPolygon::parse_points(const char *data);
	//�p�X�ɕϊ�
	virtual SvgPath *cnv_to_path();
	//
	const SVGCOORDS *coords() const {return &m_coords; }
};

#endif
