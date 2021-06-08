#ifndef _SVGPOLYLINE_H_
#define _SVGPOLYLINE_H_

#include "SvgObject.h"
#include "SvgPath.h"

class SvgPolyline : public SvgObject {
	typedef SvgObject	super;
public:

protected:
	SVGCOORDS	m_coords;
public:
	//�R���X�g���N�^
	SvgPolyline(SvgParser *parser, SvgObject *parent)
		: SvgObject(parser, parent) {
		m_type = SVG_TYPE_POLYLINE;
	}
	//�f�X�g���N�^
	virtual ~SvgPolyline();
	//�������
	virtual PARSE_RESULT parse_attribute(const char *att[]);
	//���W�f�[�^���
	PARSE_RESULT SvgPolyline::parse_points(const char *data);
	//�p�X�ɕϊ�
	virtual SvgPath *cnv_to_path();
	//
	const SVGCOORDS *coords() const {return &m_coords; }
};

#endif
