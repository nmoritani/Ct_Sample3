#ifndef _SVGRECT_H_
#define _SVGRECT_H_

#include "SvgObject.h"
#include "SvgPath.h"

class SvgRect : public SvgObject {
	typedef SvgObject	super;
public:

protected:
	float		m_x;
	float		m_y;
	float		m_width;
	float		m_height;
	float		m_rx;
	float		m_ry;
public:
	//�R���X�g���N�^
	SvgRect(SvgParser *parser, SvgObject *parent)
		: SvgObject(parser, parent) {
		m_type = SVG_TYPE_RECT;
		//�����l�ݒ�
		m_x = 0.0f;
		m_y = 0.0f;
		m_rx = -1.0f;
		m_ry = -1.0f;
	}
	//�f�X�g���N�^
	virtual ~SvgRect();
	//�������
	virtual PARSE_RESULT parse_attribute(const char *att[]);
	//������͌��ʂ��`�F�b�N	
	virtual PARSE_RESULT parse_attribute_end();
	//�p�X�ɕϊ�
	virtual SvgPath *cnv_to_path();
	//
	float x() const { return m_x; }
	float y() const { return m_y; }
	float width() const { return m_width; }
	float height() const { return m_height; }
	float rx() const { return m_rx; }
	float ry() const { return m_ry; }
};

#endif
